# PSET 9 - Finance 
This is a stock tracker app build using Flask, sqlite3, python, and jinja2

## How to use:
1) First you need to generate an API key from https://iexcloud.io/
2) Run the following commands to run the flask server locally after cloning this repo:

'''bash
~ % python3 -m venv venv
~ % source venv/bin/activate
(venv) ~ % pip install -r requirements.txt
(venv) ~ % export API_Key=api_key_from_https://iexcloud.io/console/home
(venv) ~ % flask run
'''