namespace Lab2.Abstractions
{
    public interface IExceptionInfoSender
    {
        bool Send(string exceptionTypeName);
    }
}