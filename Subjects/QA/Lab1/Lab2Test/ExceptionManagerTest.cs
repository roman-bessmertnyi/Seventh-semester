using System;
using System.Collections.Generic;
using System.Linq;
using Lab2.Abstractions;
using Lab2.Implementation;
using Moq;
using NUnit.Framework;

namespace Lab2Test
{
    public class ExceptionManagerTest
    {
        private ExceptionManager _exceptionManager;

        [SetUp]
        public void SetUp()
        {
            var configMock = new Mock<ICriticalExceptionsConfiguration>();
            configMock.Setup(configuration => configuration.CriticalExceptionTypes)
                .Returns(new List<Type>
                {
                    typeof(NotImplementedException),
                    typeof(NotSupportedException),
                    typeof(IndexOutOfRangeException)
                });
            var criticalExceptionsConfiguration = configMock.Object;

            var checkerMock = new Mock<ICriticalExceptionsChecker>();
            checkerMock.Setup(checker => checker.IsCritical(It.IsAny<Exception>()))
                .Returns((Exception exception) =>
                criticalExceptionsConfiguration.CriticalExceptionTypes.Any(type => type == exception.GetType()));

            var criticalExceptionsChecker = checkerMock.Object;

            var senderMock = new Mock<IExceptionInfoSender>();
            senderMock.Setup(sender => sender.Send(It.IsIn("IndexOutOfRangeException"))).Returns(false);
            senderMock.Setup(sender => sender.Send(It.IsNotIn("IndexOutOfRangeException"))).Returns(true);
            senderMock.Setup(sender => sender.Send(It.IsAny<string>())).Callback(() => );
            var exceptionInfoSender = senderMock.Object;

            var factoryMock = new Mock<IExceptionInfoSenderFactory>();
            factoryMock.Setup(factory => factory.Create()).Returns(exceptionInfoSender);

            var exceptionInfoSenderFactory = factoryMock.Object;

            _exceptionManager = new ExceptionManager(criticalExceptionsChecker, exceptionInfoSenderFactory);
        }

        [Test, TestCaseSource(typeof(IsCriticalTestCaseData))]
        public bool IsCritical_ValidData_ReturnsBool(Exception exception)
        {
            var isCritical = _exceptionManager.IsCritical(exception);

            return isCritical;
        }

        [Test]
        public void IsCritical_InValidData_ThrowsException()
        {
            Assert.Throws<ArgumentNullException>(() => _exceptionManager.IsCritical(null));
        }

        [Test, TestCaseSource(typeof(HandleTestCaseData))]
        public (int criticalCount, int nonCriticalCount, int sedningFailures) Handle_ValidData_IncrementsCountersWithSendingFailures(Exception exception)
        {
            _exceptionManager.Handle(exception);

            return (_exceptionManager.CriticalExceptionsPassed, _exceptionManager.NonCriticalExceptionsPassed, _exceptionManager.SendingFailuresCount);
        }

        [Test]
        public void Handle_InValidData_ThrowsException()
        {
            Assert.Throws<ArgumentNullException>(() => _exceptionManager.Handle(null));
        }
    }
}