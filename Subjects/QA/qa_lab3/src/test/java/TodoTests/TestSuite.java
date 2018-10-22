package TodoTests;

import org.junit.runner.RunWith;
import org.junit.runners.Suite;

@RunWith(Suite.class)

@Suite.SuiteClasses({
        NewTodo.class ,
        NoTodos.class,
        WhenPageIsInitiallyOpened.class,
        Editing.class
})
public class TestSuite {
}
