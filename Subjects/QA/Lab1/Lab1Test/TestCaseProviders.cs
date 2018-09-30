using System;
using System.Collections;
using System.Collections.Generic;
using NUnit.Framework;

namespace Lab1Test
{
    public class HandleTestCaseData : IEnumerable<TestCaseData>
    {
        public IEnumerator<TestCaseData> GetEnumerator()
        {
            yield return new TestCaseData(new NotImplementedException()).Returns((1, 0));
            yield return new TestCaseData(new NotSupportedException()).Returns((1, 0));
            yield return new TestCaseData(new ArgumentNullException()).Returns((0, 1));
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return GetEnumerator();
        }
    }

    public class IsCriticalTestCaseData : IEnumerable<TestCaseData>
    {
        public IEnumerator<TestCaseData> GetEnumerator()
        {
            yield return new TestCaseData(new NotImplementedException()).Returns(true);
            yield return new TestCaseData(new NotSupportedException()).Returns(true);
            yield return new TestCaseData(new InvalidOperationException()).Returns(false);
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return GetEnumerator();
        }
    }
}