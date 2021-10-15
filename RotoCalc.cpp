#include "RotoCalc.hpp"

const string version("1.0");
class OptionsExitsProgram : public exception
{
    const char * what () const throw ()
    {
        cout << "Exitting Program." << endl;
        exit(0);
        return "Program end";
    }
};

enum StatList
{
    Triples,
    Asts,
    Blks,
    FG,
    FT,
    PTS,
    REB,
    STL,
    TO
};
struct Player
{
    string teamName;
    deque<string> rawStats;
    vector<float> stats;
    float finalScore;
    int index;

    Player(string content)
    {
        boost::char_separator<char> sep (",");
        boost::tokenizer<boost::char_separator<char>> t(content, sep);
        for(string part : t)
            rawStats.push_back(boost::lexical_cast<string>(part));
        
        index = boost::lexical_cast<int>(rawStats[0]);
        teamName = boost::lexical_cast<string>(rawStats[10]);
        rawStats.pop_front();
        rawStats.pop_back();
        finalScore = 0;
        for(auto& stat : rawStats)
        {
            auto casted = boost::lexical_cast<float>(stat);
            stats.push_back(casted);
        }
    }

    float GetTriples()
    {
        return stats[Triples];
    }

    float GetAssists()
    {
        return stats[Asts];
    }

    float GetBlocks()
    {
        return stats[Blks];
    }

    float GetFG()
    {
        return stats[FG];
    }

    float GetFT()
    {
        return stats[FT];
    }

    float GetPoints()
    {
        return stats[PTS];
    }

    float GetRebounds()
    {
        return stats[REB];
    }

    float GetSteals()
    {
        return stats[STL];
    }

    float GetTurnovers()
    {
        return stats[TO];
    }
    float GetFinalScore()
    {
        return finalScore;
    }

    string GetTeamName()
    {
        return teamName;
    }

    void AddPoints(int points)
    {
        finalScore += points;
    }

    void PrintStats()
    {
        for(int i = 0; i < stats.size(); i++)
            cout << "Stat at " << i << ": " << stats.at(i) << endl;;
    }
};

struct League
{
    vector<Player> players;
    string name;
    string id;

    League() {}

    void AddPlayer(Player& p)
    {
        players.emplace_back(p);
    }

    void PrintPlayers()
    {
        for(int i = players.size()-1; i >= 0; i--)
        {
            cout << endl;
            cout << "Player: " << players[i].GetTeamName() << endl;      
            cout << "Rank: " << (players.size()-i) << endl;
            cout << "Final Score: " << players[i].GetFinalScore() << endl;
        }
    }

    void RotoCalc()
    {
        for(int i = Triples; i < TO; i++)
        {
            switch(i) {
                case Triples:
                    sort(players, Triples);
                    cout << "Awarding for 3PM" << endl;
                    award();
                    break;
                case Asts:
                    sort(players, Asts);
                    cout << "Awarding for AST" << endl;
                    award();
                    break;
                case Blks:
                    sort(players, Blks);
                    cout << "Awarding for BLK" << endl;
                    award();
                    break;
                case FG:
                    sort(players, FG);
                    cout << "Awarding for FG%" << endl;
                    award();
                    break;
                case FT:
                    sort(players, FT);
                    cout << "Awarding for FT%" << endl;
                    award();
                    break;
                case PTS:
                    sort(players, PTS);
                    cout << "Awarding for PTS" << endl;
                    award();
                    break;
                case REB:
                    sort(players, REB);
                    cout << "Awarding for REB" << endl;
                    award();
                    break;
                case STL:
                    sort(players, STL);
                    cout << "Awarding for STL" << endl;
                    award();
                    break;
                case TO:
                    sort(players, TO);
                    cout << "Awarding for TO" << endl;
                    award();
                    break;
            }
        }
        sortFinal(players);
    }

    void sort(vector<Player>& players, int option)
    {
        for(int i = 0; i < players.size() - 1; i++)
        {
            for(int j = 0; j < players.size() - i - 1; j++)
            {
                if(option == Triples)
                {
                    if(players[j].GetTriples() > players[j+1].GetTriples())
                    {
                        auto p = players[j];
                        players[j] = players[j+1];
                        players[j+1] = p;

                    }
                } else if(option == Asts)
                {
                    if(players[j].GetAssists() > players[j+1].GetAssists())
                    {
                        Player p = players[j];
                        players[j] = players[j+1];
                        players[j+1] = p;
                    }
                } else if(option == Blks)
                {
                    if(players[j].GetBlocks() > players[j+1].GetBlocks())
                    {
                        Player p = players[j];
                        players[j] = players[j+1];
                        players[j+1] = p;
                    }
                } else if(option == FG)
                {
                    if(players[j].GetFG() > players[j+1].GetFG())
                    {
                        Player p = players[j];
                        players[j] = players[j+1];
                        players[j+1] = p;
                    }
                } else if(option == FT)
                {
                    if(players[j].GetFT() > players[j+1].GetFT())
                    {
                        Player p = players[j];
                        players[j] = players[j+1];
                        players[j+1] = p;
                    }
                } else if(option == PTS)
                {
                    if(players[j].GetPoints() > players[j+1].GetPoints())
                    {
                        Player p = players[j];
                        players[j] = players[j+1];
                        players[j+1] = p;
                    }
                } else if(option == REB)
                {
                    if(players[j].GetRebounds() > players[j+1].GetRebounds())
                    {
                        Player p = players[j];
                        players[j] = players[j+1];
                        players[j+1] = p;
                    }
                } else if(option == STL)
                {
                    if(players[j].GetSteals() > players[j+1].GetSteals())
                    {
                        Player p = players[j];
                        players[j] = players[j+1];
                        players[j+1] = p;
                    }
                } else if(option == TO)
                {
                    if(players[j].GetTurnovers() < players[j+1].GetTurnovers())
                    {
                        Player p = players[j];
                        players[j] = players[j+1];
                        players[j+1] = p;
                    }
                }
            }
        }
    }

    void award()
    {
        for(int i = 0; i < players.size(); i++)
        {
            int points = i+1;
            cout << "\tAdding " << points << " to team: " << players[i].GetTeamName() << endl;
            players[i].AddPoints(points);
        }
    }

    void sortFinal(vector<Player>& players)
    {
        for(int i = 0; i < players.size() - 1; i++)
        {
            for(int j = 0; j < players.size() - i - 1; j++)
            {
                if(players[j].GetFinalScore() > players[j+1].GetFinalScore())
                {
                    auto p = players[j];
                    players[j] = players[j+1];
                    players[j+1] = p;
                }
            }
        }
    }

};


class Options {
public:
    string swid;
    string s2;
    string leagueId;
    string leagueYear;
    string isPublic;
    string config_file;
    string datafile;
    string leagueName;

    Options()
    {
        SetOptions();
    }

    void ParseOptions(int argc, char* argv[])
    {
        ParseCommandLine(argc,argv);
        CheckForHelp();
        CheckForVersion();
        ParseConfigFiles();
        ParseDefualtConfig();
    }

    string Id()
    {
        return results["id"].as<string>();
    }

    string SWID()
    {
        return results["swid"].as<string>();
    }

    string S2()
    {
        return results["espn_s2"].as<string>();
    }

    string Year()
    {
        return results["year"].as<string>();
    }

    string Config()
    {
        return results["config"].as<string>();
    }

    string Name()
    {
        return results["name"].as<string>();
    }

    string Datafile()
    {
        return results["datafile"].as<string>();
    }
    
    
    bool CheckHiddenOptions()
    {
        if(this->Name() == "default" || this->Datafile() == "empty.csv")
            return false;
        else
            return true;
    }

private:
    void SetOptions()
    {
        SetCLIOptions();
        SetGenericOptions();
        SetConfigOptions();
    }

    void SetCLIOptions()
    {
        cli_options.add_options()
            ("config,c", po::value<string>(&config_file)->default_value("Default_Config.ini")->required(), "name of a file of a configuration")
            ("public,p","select this option if your league is public. No cookies are needed for this option")
            ("id", po::value<string>(&leagueId), "Input your ESPN leagueId")
            ("year,y", po::value<string>(&leagueYear)->default_value("2020"), "Input league year you want stats for. Make sure that there was a valid league for that year.")
            ("name,n", po::value<string>(&leagueName), "Input your league name. Optional")
            ;

            positional_options.add("config", 1);
    }

    void SetGenericOptions()
    {
        generic_options.add_options()
            ("version,V", "print version string")
            ("help,H", "produce help message")
            ;
    }

    void SetConfigOptions()
    {
        config_options.add_options()
            ("swid,s", po::value<string>(&swid)->default_value("SWID"))
            ("espn_s2,e", po::value<string>(&s2)->default_value("ESPN_S2"))
            ("id,I", po::value<string>(&leagueId)->default_value("123456"))
            ("datafile", po::value<string>(&datafile)->default_value("empty.csv"))
            ("name,n", po::value<string>(&leagueName)->default_value("default"))
            ;

        po::store(po::command_line_parser(0, 0).options(config_options).run(), results);
        po::notify(results);
    }

    void ParseCommandLine(int argc, char* argv[])
    {
        po::options_description cmd;
        cmd.add(cli_options).add(generic_options);
        po::store(po::command_line_parser(argc, argv).
                options(cmd).positional(positional_options).run(), results);
        notify(results);
    }

    void CheckForHelp()
    {
        if (results.count("help"))
        {
            PrintHelp();
        }
    }

    void PrintHelp()
    {
        cout << "Standard Options:" << endl;
        cout << generic_options << endl;
        cout << "Argument List" << endl;
        cout << cli_options << endl;
        cout << "Private League Configuration Options - Set these with a configuration file:" << endl;
        cout << config_options << endl;
        throw OptionsExitsProgram();
    }

    void CheckForVersion()
    {
        if(results.count("version"))
            PrintVersion();
    }

    void PrintVersion()
    {
        cout << "ESPN Roto Calc " << version << endl;
        throw OptionsExitsProgram();
    }

    void LoadConfigFile(string filename)
    {
        bool ALLOW_UNREGISTERED = true;
        po::options_description config_opts;
        config_opts.add(config_options).add(generic_options);

        ifstream cfg_file(filename.c_str());
        if(cfg_file)
        {
            po::store(po::parse_config_file(cfg_file, config_opts, ALLOW_UNREGISTERED), results);
            po::notify(results);
        }
    }

    void ParseConfigFiles()
    {
        if(results.count("config"))
        {
            auto file = results["config"].as<string>();
            LoadConfigFile(file);
        }
    }

    void ParseDefualtConfig()
    {
        LoadConfigFile("Default_Confing.ini");
    }

    po::variables_map results;
    po::options_description generic_options;
    po::options_description config_options;
    po::options_description cli_options;
    po::positional_options_description positional_options;
};

void PrintOptions(Options o)
{
    cout << "=============================" << endl << endl;
    cout << "Program Options: " << endl;
    auto config = o.Config();
    if(config.length())
    {
        cout << "Input config file: " << config << endl;
    }
    auto swid = o.SWID();
    if(swid.length())
    {
        cout << "SWID From config is: " << swid << endl;
    }
    auto s2 = o.S2();
    if(s2.length())
    {
        cout << "ESPN_S2 From config is : " << s2 << endl << endl;
    }
    cout << "=============================" << endl << endl;
    auto year = o.Year();
    if(year.length())
    {
        cout << "Roto scores for league year: " << year << endl;
    }

    auto id = o.Id();
    if(id.length())
    {
        cout << "LeagueId: " << id << endl << endl;;
    }
    cout << "=============================" << endl;
}

void CheckForDefaults(Options options)
{
     cout << "Checking: " << options.SWID() << endl;
    if(options.SWID() == "SWID")
    {
        cout << "SWID Cookie was not configured properly. If your league is public, run with -p." << endl;
        throw OptionsExitsProgram();
    }
     cout << "Checking: " << options.S2() << endl;
    if(options.S2() == "S2")
    {
        cout << "ESPN_S2 Cookie was not configured properly. If your league is public, run with -p." << endl;
        throw OptionsExitsProgram();
    }
     cout << "Checking: " << options.Id() << endl;
    if(options.Id() == "123456")
    {
        cout << "leagueId was not specified. leagueId is required for the program to run. Set this value in the configuration file, or by passing it with -I" << endl;
        throw OptionsExitsProgram();
    }
}

bool CheckDirectory(path& dir, string datafile)
{
    directory_iterator end;
    for(directory_iterator i(dir); i != end; ++i)
    {
        path p = i->path();
        if(p.filename() == datafile)
            return true;
    }
    return false;
}


int main(int argc, char* argv[])
{
    League l;
    Options opts;
    try
    {
        opts.ParseOptions(argc, argv);
        PrintOptions(opts);
        CheckForDefaults(opts);
        vector<string> args {"python3","../fantasy.py", opts.SWID(), opts.S2(), opts.Id(), opts.Datafile(), opts.Config(), opts.Year()};
        cout << "Fetching Data.." << endl;
        auto cmd = join(args, " ");
        system(cmd.c_str());

    }
    catch(const exception& e)
    {
        cerr << "Exception encountered while executing fantasy.py." << endl;
        cerr << e.what() << endl;
    }

    auto cwd = current_path();
    if(CheckDirectory(cwd, opts.Datafile()))
    {
        try
        {
            string content;
            ifstream ifs;
            ifs.open(opts.Datafile(), ios::in);
            cout << "Checking datafile: " << opts.Datafile() << endl;
            if(ifs)
            {
                getline(ifs, content);

                while(getline( ifs, content))
                {
                    Player p(content);
                    l.AddPlayer(p);
                }
                ifs.close();
            } else {
                cout << "Datafile could not be read" << endl;
            }
        }
        catch(const exception& e)
        {
            cerr << e.what() << endl;
        }
        
    } else {
        throw OptionsExitsProgram();
    }

    l.RotoCalc();
    l.PrintPlayers();

    cout << "=============================" << endl;
    return 0;
}