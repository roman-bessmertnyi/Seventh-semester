using System;

namespace Lab1
{
    public interface IExceptionManager
    {
        bool IsCritical(Exception exception);
        void Handle(Exception exception);
    }
}