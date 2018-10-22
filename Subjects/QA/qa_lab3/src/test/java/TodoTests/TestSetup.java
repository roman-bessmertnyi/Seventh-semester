package TodoTests;

import org.junit.After;
import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.Suite;
import org.openqa.selenium.By;
import org.openqa.selenium.Keys;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.chrome.ChromeDriver;
import org.openqa.selenium.support.ui.ExpectedConditions;
import org.openqa.selenium.support.ui.WebDriverWait;


public class TestSetup {
    WebDriver driver;
    WebDriverWait angularWaiter;
    String baseUrl;

    Page page;

    TestOperations testOps;

    String TODO_ITEM_ONE = "buy some cheese";
    String TODO_ITEM_TWO = "feed the cat";
    String TODO_ITEM_THREE = "book a doctors appointment";

    public void createStandardItems(){
        WebElement new_todo = page.waitForElement(page.getNewInputCss());

        new_todo.sendKeys(TODO_ITEM_ONE + Keys.RETURN);
        new_todo.sendKeys(TODO_ITEM_TWO + Keys.RETURN);
        new_todo.sendKeys(TODO_ITEM_THREE + Keys.RETURN);
    }

    @Before
    public void SetUp() {
        System.setProperty("webdriver.chrome.driver", System.getProperty("user.dir") + "\\chromedriver.exe");
        driver = new ChromeDriver();;

        angularWaiter = new WebDriverWait(driver, 10);

        baseUrl = "http://todomvc.com/examples/angularjs/#/";

        page = new Page(driver);

        testOps = new TestOperations(page);
    }

    @Before
    public void launchBrowser() {
        driver.get(baseUrl);
        angularWaiter.until(ExpectedConditions.visibilityOfElementLocated(By.xpath("//body/ng-view")));
    }

    @After
    public void closeBrowser() {
        driver.close();
    }
}
