using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;

[assembly:InternalsVisibleTo("Lab1Test")]
namespace Lab1
{
    internal class ExceptionManager : IExceptionManager
    {
        public int CriticalExceptionsPassed { get; private set; } = 0;

        public int NonCriticalExceptionsPassed { get; private set; } = 0;

        private readonly ICollection<Type> _criticalExceptionTypes = new List<Type>
        {
            typeof(NotImplementedException),
            typeof(NotSupportedException)
        };

        public bool IsCritical(Exception exception)
        {
            if (exception == null)
            {
                throw new ArgumentNullException(nameof(exception));
            }

            return _criticalExceptionTypes.Any(type => type == exception.GetType());
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
            }
            else
            {
                NonCriticalExceptionsPassed++;
            }
        }
    }
}