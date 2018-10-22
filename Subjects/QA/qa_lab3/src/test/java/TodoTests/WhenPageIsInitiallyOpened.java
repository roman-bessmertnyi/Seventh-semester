package TodoTests;

import org.junit.Test;

public class WhenPageIsInitiallyOpened extends TestSetup {
    @Test
    public void shouldFocusOnTheTodoInputField() {
        testOps.assertNewInputFocused();
    }
}
