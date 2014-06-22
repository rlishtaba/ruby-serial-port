Feature: Connection

  As an QA
  in order to test connection object I will create new one and ensure that it is opened and can be closed

  Scenario: Should have an ability to check open or not

    Given connection instance "should" be available
     Then I "close" connection
      And connection instance "should not" be available