package TodoTests;

import org.junit.Test;
import org.openqa.selenium.Keys;
import org.openqa.selenium.WebElement;

public class NewTodo extends TestSetup {
    @Test
    public void shouldAllowMeToAddTodoItems() throws Exception {
        WebElement new_todo = page.waitForElement(page.getNewInputCss());

        new_todo.sendKeys(TODO_ITEM_ONE);
        new_todo.sendKeys(Keys.RETURN);
        testOps.assertItems(new String[]{TODO_ITEM_ONE});

        new_todo.sendKeys(TODO_ITEM_TWO);
        new_todo.sendKeys(Keys.RETURN);
        testOps.assertItems(new String[]{TODO_ITEM_ONE, TODO_ITEM_TWO});
    }
}
