# CryptoTaxCalculator
Calculates capital gains (or losses) in the format of Form 8949 and Schedule D, after importing a buy/sell history.
***

This contains two interactive methods, buy and sell. At this time, you can only buy and sell one type of asset (in this case coin) at a time.

### Report ###
![ScreenShot](images/CTcode.png)
This is an early version of the program where transactins are entered manually by editing the main method. The parameters for transactions are described below.

![ScreenShot](images/CTreport.png)
These lines are autonatically converted to a report printed to the terminal.

#### Buy ####
---

Buy takes three parameters:
-Amount: amount of coin
-Date: In yyyy-mm-dd format
-costPerUnit: Price (at the time) of 1 of the coin.

#### Sell ####
---

Sell also takes three (very similar) parameters:
-Amount: amount of coin
-Date: In yyyy-mm-dd format
-proceedsPerUnit: Price (at the time) of 1 of the coin.


### Limitations ###
There is an issue with the Transaction linked list where it most likely fails after the first attempt to sell. Check back later or message me with any questions or concerns...