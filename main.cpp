#include <bits/stdc++.h>
#include "files.h"

typedef struct Team{
    std::string name;
    std::string integrants[32];
    std::string previous[32];
    int replayam;
    std::string replay[32];
    bool operator < (const Team &b){
        return this->name < b.name;
    }
}team;

FILE *teamdata;
FILE *replays;
FILE *prev;
FILE *players;
FILE *result;

int teamam, teamint;
char read[32];
team teams[16];
std::string teamnames[16];
std::map<std::string, std::map<std::string, int> > matches;
std::map<std::string, int> matcham;
std::map<std::string, std::string> generals;
std::string seeding[32];

int selectMatches(int x){
    if(x == teamam){
        return 1;
    }
    if(matcham[teams[x].name] == teamint){
        return selectMatches(x+1);
    }
    bool found = true;
    for(int i = 0; i < teamam; i++){
        if(matches[teams[x].name][teamnames[i]] == -1){
            found = false;
            if(matcham[teamnames[i]] < teamint){
                matches[teams[x].name][teamnames[i]] = 1;
                matches[teamnames[i]][teams[x].name] = 1;
                matcham[teams[x].name]++;
                matcham[teamnames[i]]++;
                if(selectMatches(x)){
                    return 1;
                }
                matches[teams[x].name][teamnames[i]] = -1;
                matches[teamnames[i]][teams[x].name] = -1;
                matcham[teams[x].name]--;
                matcham[teamnames[i]]--;
            }
        }
    }
    if(found){
        for(int i = 0; i < teamam; i++){
            if(matches[teams[x].name][teamnames[i]] == -2){
                found = false;
                if(matcham[teamnames[i]] < teamint){
                    matches[teams[x].name][teamnames[i]] = 1;
                    matches[teamnames[i]][teams[x].name] = 1;
                    matcham[teams[x].name]++;
                    matcham[teamnames[i]]++;
                    if(selectMatches(x)){
                        return 1;
                    }
                    matches[teams[x].name][teamnames[i]] = -2;
                    matches[teamnames[i]][teams[x].name] = -2;
                    matcham[teams[x].name]--;
                    matcham[teamnames[i]]--;
                }
            }
        }
    }
    if(found){
        for(int i = 0; i < teamam; i++){
            if(teams[x].name != teamnames[i]){
                if(matcham[teamnames[i]] < teamint){
                    matches[teams[x].name][teamnames[i]]++;
                    matches[teamnames[i]][teams[x].name]++;
                    matcham[teams[x].name]++;
                    matcham[teamnames[i]]++;
                    if(selectMatches(x)){
                        return 1;
                    }
                    matches[teams[x].name][teamnames[i]]--;
                    matches[teamnames[i]][teams[x].name]--;
                    matcham[teams[x].name]--;
                    matcham[teamnames[i]]--;
                }
            }
        }
    }
    return 0;
}

int genMatches(int x){
    if(x == teamam){
        return 1;
    }
    for(int i = 0; i < teamam; i++){
        if(matches[teams[x].name][teamnames[i]] > 0){
            if(generals[teamnames[i]].size() == 0){
                generals[teamnames[i]] = teams[x].name;
                if(genMatches(x+1)){
                    return 1;
                }
                generals[teamnames[i]].clear();
            }
        }
    }
    return 0;
}

int main(){
    srand(time(NULL));
    srand(rand());
    readFile(&teamdata, "War/teams.txt");
    readFile(&replays, "War/replays.txt");
    readFile(&prev, "War/round.txt");
    readFile(&players, "War/players.txt");
    writeFile(&result, "War/matchups.txt");
    fscanf(teamdata, "%d %d", &teamam, &teamint);
    for(int i = 0; i < teamam; i++){
        fscanf(teamdata, " %[^\n]", read);
        teams[i].name = read;
        teamnames[i] = teams[i].name;
        for(int e = 0; e < teamint; e++){
            fscanf(players, " %[^\n]", read);
            teams[i].integrants[e] = read;
            fscanf(prev, " %[^\n]", read);
            teams[i].previous[e] = read;
        }
        fscanf(replays, "%d", &teams[i].replayam);
        for(int e = 0; e < teams[i].replayam; e++){
            fscanf(replays, " %[^\n]", read);
            teams[i].replay[e] = read;
        }
    }
    closeWriteFile(teamdata);
    closeWriteFile(players);
    closeWriteFile(replays);
    closeWriteFile(prev);

    //get teams to play
    for(int i = 0; i < teamam; i++){
        for(int e = 0; e < teamam; e++){
            if(i == e){
                matches[teams[i].name][teamnames[e]] = -3;
            } else {
                matches[teams[i].name][teamnames[e]] = 1;
            }
        }
    }
    for(int i = 0; i < teamam; i++){
        matcham[teams[i].name] = 0;
        for(int e = 0; e < teamint; e++){
            matches[teams[i].name][teams[i].previous[e]] = -1;
        }
        for(int e = 0; e < teams[i].replayam; e++){
            matches[teams[i].name][teams[i].replay[e]] = -2;
        }
    }
    for(int i = 0; i < teamam; i++){
        for(int e = 0; e < teamam; e++){
            if(matches[teamnames[i]][teamnames[e]] == 1){
                matcham[teamnames[i]]++;
            }
        }
    }
    std::random_shuffle(teams, teams+teamam);
    std::random_shuffle(teamnames, teamnames+teamam);
    std::random_shuffle(teams, teams+teamam);
    std::random_shuffle(teamnames, teamnames+teamam);
    std::random_shuffle(teams, teams+teamam);
    std::random_shuffle(teamnames, teamnames+teamam);
    selectMatches(0);
    genMatches(0);
    std::sort(teams, teams+teamam);
    std::sort(teamnames, teamnames+teamam);
    for(int i = 0; i < teamam; i++){
        fprintf(result, "%s\n", teams[i].name.c_str());
        fprintf(result, "Faced:\n");
        for(int e = 0; e < teamint; e++){
            fprintf(result, "%s ", teams[i].previous[e].c_str());
        }
        fprintf(result, "\nReplayed");
        for(int e = 0; e < teams[i].replayam; e++){
            fprintf(result, " %s", teams[i].replay[e].c_str());
        }
        fprintf(result, "\nPlaying:\n");
        for(int e = 0; e < teamam; e++){
            if(matches[teams[i].name][teamnames[e]] > 0){
                fprintf(result, "%dx %s, ", matches[teams[i].name][teamnames[e]], teamnames[e].c_str());
            }
        }
        fprintf(result, "\n%s vs %s\n", teams[i].integrants[0].c_str(), generals[teams[i].name].c_str());
        int z = 1;
        for(int e = 0; e < teamam; e++){
            if(teamnames[e] == generals[teams[i].name]){
                matches[teams[i].name][teamnames[e]]--;
            }
            while(matches[teams[i].name][teamnames[e]] > 0){
                seeding[z++] = teamnames[e];
                matches[teams[i].name][teamnames[e]]--;
            }
        }
        std::random_shuffle(seeding+1, seeding+z);
        std::random_shuffle(seeding+1, seeding+z);
        for(int e = 1; e < teamint; e++){
            fprintf(result, "%s vs %s\n", teams[i].integrants[e].c_str(), seeding[e].c_str());
        }
        fprintf(result, "\n");
    }
    closeReadFile(result);
    return 0;
}
