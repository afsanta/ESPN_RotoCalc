import requests
import json
import pandas as pd
import sys
import enum


pd.set_option("display.max_rows", None, "display.max_columns", None)
argc = len(sys.argv)

class Options(enum.IntEnum):
    SWID = 1
    S2 = 2
    ID = 3
    DATA = 4
    CONFIG = 5
    YEAR = 6

# print("Running script: ", sys.argv[0])

swid_cookie = sys.argv[Options.SWID]
espn_s2_cookie = sys.argv[Options.S2]
leagueId = sys.argv[Options.ID]
datafile = sys.argv[Options.DATA]
configfile = sys.argv[Options.CONFIG]
leagueYear = sys.argv[Options.YEAR]



# print(swid_cookie, espn_s2_cookie, leagueId, leagueYear)


# This is the request url to API endpoint
url = 'https://fantasy.espn.com/apis/v3/games/fba/seasons/' + leagueYear + '/segments/0/leagues/' + leagueId

# The parameter needed to get the data you want
statsPayload = {
'view': 'mTeam',
}

leagueNamePayload = {
    'view': 'mSettings',
}
cookies = {"swid": swid_cookie,
            "espn_s2": espn_s2_cookie
}


# Return the data (which is in json format) and load into pytohn
jsonData = requests.get(url, params=statsPayload, cookies=cookies).json()

settings = requests.get(url, params=leagueNamePayload, cookies=cookies).json()

league_name = settings['settings']['name']
league_name = league_name.replace(" ", "_")
csv_name = configfile + "_" + leagueYear + ".csv"

ofp = open(configfile, 'w')
for i in range(1,argc):
    if i == 1:
        ofp.write('swid = ' + swid_cookie)
    if i == 2:
        ofp.write('\nespn_s2 = ' + espn_s2_cookie)
    if i == 3:
        ofp.write('\nid = ' + leagueId)
    if i == 4:
        ofp.write('\ndatafile = ' + csv_name)
    if i == 5:
        ofp.write('\nname = ' + league_name)

ofp.write('\n')
ofp.close()



stats_cols = {
'0': 'PTS',
'1': 'BLK',
'2': 'STL',
'3': 'AST',
'6': 'REB',
'11': 'TO',
'17': '3PM',
'19': 'FG%',
'20': 'FT%'}

# This will iterate through each of the items in the specific key:value
stats_df = pd.DataFrame()
stats = jsonData['teams']

for each in stats:
    user = pd.DataFrame([[each['abbrev']]],
                        columns=['abbrev'])

    temp_stat_df = pd.DataFrame([each['valuesByStat']])
    temp_df = pd.concat([temp_stat_df, user], sort=True, axis=1)
    temp_df = temp_df.rename(columns=stats_cols)
    stats_df = stats_df.append(temp_df, sort=True).reset_index(drop=True)

stats_df.drop(columns=['13', '14', '15', '16'], inplace=True)
stats_df.rename(columns=stats_cols, inplace=True)
# print (stats_df)

stats_df.to_csv(csv_name)

print("Wrote league stats to " + csv_name)