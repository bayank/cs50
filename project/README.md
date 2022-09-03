# Congress stock tracker
#### Video Demo:  https://youtu.be/s83eNAVwTvM
#### Description:
This project makes use of publicly available data about disclosed stock trading transactions by members of congress. Why would we want to do this? Our elected officials have regular access to information that could substantially impact the stock market or individual securities listed on public exchanges. There are meaningful conclusions we can draw from such data, as it can serve as an indicator for invesotrs where the trends are.

A couple benefits I can think for why we should care abuot this data:
1) A savvy investor could stand to profit by mirroring similar transactions based on the available data
    A)That same savvy investor realizes that such data is already priced in to many securities before the data becomes public, wiping all gains to be had, and thus the savvy investor proves that the whole system is rigged against the little retail inversor.
2) Ensuring accountability of our elected officials
    A)An easy example: Check to see if an elected official invested heavily into fossil fuels and non-renewable energy companies while they pledged to support the renewable energy industry and based their campaign on environmental causes.

How does it work?

The primary source of this data comes from https://senatestockwatcher.com/api which hosted by an individual who shares a passion for compiling and hosting this information. This service would normally be hosted as an api that we could talk to and request from our frontend. Becuase generating these responses dynamically costs money, the service provider has chosen to host this data as a static .json file. The upstream source of this data comes from official US governemnt website available here: https://efdsearch.senate.gov/search/home/ .

This app mkes use of the requests library to establish a connection and fetch the .json payload. Then we can use the JSON library to parse this into a python dictionary for further processing.

In this first iteration we'll process this data and sort the list of members by the number of transactions completed for the time interval of the full dataset. This will show us the most active members, which I think is an interesting data point.

I intend to work on this project beyond CS50 and have some ideas for future iterations. I would like to visualize this dataset in a webapp. Another idea is to look for trends in the dataset using machine learning in a vein attempt to predict the future.

