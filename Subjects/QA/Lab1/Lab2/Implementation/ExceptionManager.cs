using System;
using Lab1;
using Lab2.Abstractions;

namespace Lab2.Implementation
{
    public class ExceptionManager : IExceptionManager
    {
        public int CriticalExceptionsPassed { get; private set; } = 0;

        public int NonCriticalExceptionsPassed { get; private set; } = 0;

        public int SendingFailuresCount { get; private set; } = 0;

        private readonly IExceptionInfoSender _exceptionInfoSender;
        private readonly ICriticalExceptionsChecker _criticalExceptionsChecker;

        public ExceptionManager(ICriticalExceptionsChecker criticalExceptionsChecker, 
            IExceptionInfoSenderFactory factory)
        {
            _criticalExceptionsChecker = criticalExceptionsChecker;
            _exceptionInfoSender = factory.Create();
        }

        public bool IsCritical(Exception exception)
        {
            if (exception == null)
            {
                throw new ArgumentNullException(nameof(exception));
            }

            return _criticalExceptionsChecker.IsCritical(exception);
        }

        public void Handle(Exception exception)
        {
            if (exception == null)
            {
                throw new ArgumentNullException(nameof(exception));
            }

            var isCritical = IsCritical(exception);

            if (isCritical)
            {
                CriticalExceptionsPassed++;
                var sentSuccessfully = _exceptionInfoSender.Send(exception.GetType().Name);

                if (!sentSuccessfully)
                {
                    SendingFailuresCount++;
                }
            }
            else
            {
                NonCriticalExceptionsPassed++;
            }
        }
    }
}