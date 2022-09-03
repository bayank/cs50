import requests
import json

data = requests.get('https://house-stock-watcher-data.s3-us-west-2.amazonaws.com/data/all_transactions.json')
data_json = data.json()

#Print some key:values from the raw json:
# for entry in data_json:
#     print(entry['representative'] + " did a " + entry['type'] + " of " + entry['ticker'] + "(" + str(entry['asset_description']) + ")" )

#Map of representatives to number of times they appear in the data, or conducted a transaction
entries_by_rep = {}

#increment the number of times each rep transacted
for entry in data_json:
    if entry["representative"]:
        try:
            entries_by_rep[entry["representative"]] += 1
        except KeyError:
            entries_by_rep[entry["representative"]] = 1

#Creat a sorted list of (representative, #number of times transacted) pairs
top_reps = sorted(entries_by_rep.items(), key=lambda x: x[1], reverse=True)

for entry in top_reps:
    print(entry)

