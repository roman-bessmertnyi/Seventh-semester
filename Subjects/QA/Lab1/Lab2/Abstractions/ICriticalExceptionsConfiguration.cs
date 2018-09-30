using System;
using System.Collections.Generic;

namespace Lab2.Abstractions
{
    public interface ICriticalExceptionsConfiguration
    {
        ICollection<Type> CriticalExceptionTypes { get; }
    }
}