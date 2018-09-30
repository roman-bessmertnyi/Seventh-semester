using System;
using Lab1;
using NUnit.Framework;
using Assert = NUnit.Framework.Assert;

namespace Lab1Test
{
    [TestOf(typeof(ExceptionManager))]
    public class ExcptionManagerTest
    {
        private ExceptionManager _exceptionManager;

        [SetUp]
        public void SetUp()
        {
            _exceptionManager = new ExceptionManager();
        }


        [Test, TestCaseSource(typeof(IsCriticalTestCaseData))]
        public bool IsCritical_ValidData_ReturnsBool(Exception exception)
        {
            var isCritical = _exceptionManager.IsCritical(exception);

            return isCritical;
        }

        [Test, TestCaseSource(typeof(HandleTestCaseData))]
        public (int criticalCount, int nonCriticalCount) Handle_ValidData_IncrementsCounters(Exception exception)
        {
            _exceptionManager.Handle(exception);

            return (_exceptionManager.CriticalExceptionsPassed, _exceptionManager.NonCriticalExceptionsPassed);
        }

        [Test]
        public void Handle_InValidData_ThrowsException()
        {
            Assert.Throws<ArgumentNullException>(() => _exceptionManager.Handle(null));
        }

        [Test]
        public void IsCritical_InValidData_ThrowsException()
        {
            Assert.Throws<ArgumentNullException>(() => _exceptionManager.IsCritical(null));
        }
    }
}