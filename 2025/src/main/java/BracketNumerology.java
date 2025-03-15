import java.util.HashMap;
import java.util.Map;
import com.opencsv.CSVReader;
import java.io.*;
import java.util.Random;

public class BracketNumerology {
    Map<Character, Double> letterScores = new HashMap<>();

    public void generate_letter_scores(String teamCsvPath) {
        //Set letterScores for each of the 26 letters

        //Initialize maps
         String letters = "abcdefghijklmnopqrstuvwxyz";
         Map<Character, Integer> letterAppearances = new HashMap<>();
         Map<Character, Double> letterRunningScores = new HashMap<>();
         for (int i=0; i<letters.length(); i++){
             char letter = letters.charAt(i);
             letterAppearances.put(letter, 0);
             letterRunningScores.put(letter, 0.0);
         }

        //open the csv
        try (FileReader fileReader = new FileReader(teamCsvPath)) {
            CSVReader csvReader = new CSVReader(fileReader);
            //cycle through lines of csv
            String[] nextLine = csvReader.readNext();//Skip the header
            while ((nextLine = csvReader.readNext()) != null) {
                String name = nextLine[0];
                int seed = Integer.parseInt(nextLine[1]);
                for (int i = 0; i < name.length(); i++) {
                    //add to running score for this letter
                    char letter = name.charAt(i);
                    double addedScore = 16.0 - seed;
                    letterAppearances.put(letter, letterAppearances.get(letter) + 1);
                    letterRunningScores.put(letter, letterRunningScores.get(letter) + addedScore);
                }
            }

            //calculate the final scores for each letter
            for (int i=0; i<letters.length(); i++){
                char letter = letters.charAt(i);
                if (letterAppearances.get(letter) == 0){
                    letterScores.put(letter, 0.0);
                }else{
                    double score = letterRunningScores.get(letter)/letterAppearances.get(letter);
                    letterScores.put(letter, score);
                }
            }

            //print the result
            System.out.println(letterScores);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }


    public void simulate_tournament(String teamCsvPath){

    }
    public void simulate_round(String teamCsvPath){

    }
    public int simulate_match(String team0, String team1){
        //Return 0 if team0 wins, 1 if team1 wins
        //Determine winner using randomness and the letter scores
        double team0Score = get_name_normalized_score(team0);
        double team1Score = get_name_normalized_score(team1);
        double total = team0Score + team1Score;

        Random random = new Random();
        double randNum = random.nextDouble();//0 to 1 inclusive
        if (randNum < team0Score/total){
            System.out.println(team0 + " beats " + team1);
            System.out.println(team0Score/total + " chance");
            return 0;
        }
        System.out.println(team1 + " beats " + team0);
        System.out.println(team1Score/total + " chance");
        return 1;
    }
    public double get_name_normalized_score(String name){
        double runningScore = 0.0;
        for (int i=0; i<name.length(); i++){
            char letter = name.charAt(i);
            runningScore += letterScores.get(letter);
        }
        return runningScore/name.length();
    }

    public static void main(String[] args){
        BracketNumerology numerology = new BracketNumerology();
        numerology.generate_letter_scores("Teams.csv");
//        numerology.simulate_tournament("Teams.csv");
//        System.out.println(numerology.simulate_match("ae","aa"));
//        System.out.print(numerology.get_name_normalized_score("aea"));
    }
}