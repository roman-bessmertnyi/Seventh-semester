using System;

namespace Lab2.Abstractions
{
    public interface ICriticalExceptionsChecker
    {
        bool IsCritical(Exception exception);
    }
}
