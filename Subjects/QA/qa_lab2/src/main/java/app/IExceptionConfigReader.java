package app;

public interface IExceptionConfigReader {
    boolean readIsCritical(Exception e);
}
