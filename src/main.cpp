#include <main.h>
#include <ismtools.h>

std::string version = "0.0.1";

std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now(); // immediately start the clock when the program is run

int verbose_flag;
int maxThreads = 0;
int cmd_flag;
UserInput userInput;

std::mutex mtx;
ThreadPool<std::function<bool()>> threadPool;
Log lg;

std::string getArgs(char* optarg, unsigned int argc, char **argv) {
    
    std::string cmd;
    bool record = false;

    for (unsigned short int arg_counter = 0; arg_counter < argc; arg_counter++) {
        
        if (optarg != argv[arg_counter] && !record) {
            continue;
        }else{
            record = true;
            if(optarg != argv[arg_counter]){
                cmd += ' ';
                cmd += argv[arg_counter];
            }
        }
    }
    
    return cmd;
    
}

int main(int argc, char **argv) {
    
    short int c; // optarg
    short unsigned int pos_op = 1; // optional arguments
    
    bool arguments = true;
    
    std::string cmd;
    
    //bool isPipe = false; // to check if input is from pipe
    
    if (argc == 1) { // ismtools with no arguments
            
        printf("ismtools [command]\n-h for additional help.\n");
        exit(0);
        
    }
    
    static struct option long_options[] = { // struct mapping long options
        {"cmd", no_argument, &cmd_flag, 1},
        {"version", no_argument, 0, 'v'},
        {"help", no_argument, 0, 'h'},
        
        {0, 0, 0, 0}
    };
    
//    const static std::unordered_map<std::string,int> tools{
//        {"something",1},
//        {"somethingelse",2}
//    };
    
    while (arguments) { // loop through argv
        
        int option_index = 0;
        
        c = getopt_long(argc, argv, "-:vh",
                        long_options, &option_index);
        
        if (c == -1) { // exit the loop if run out of options
            break;
            
        }

        switch (c) {
            case ':': // handle options without arguments
                switch (optopt) { // the command line option last matched
                    case 'b':
                        break;
                        
                    default:
                        fprintf(stderr, "option -%c is missing a required argument\n", optopt);
                        return EXIT_FAILURE;
                }
                break;
            default: // handle positional arguments
            case 0: // case for long options without short options
                
//                if (strcmp(long_options[option_index].name,"line-length") == 0)
//                  splitLength = atoi(optarg);
                
                break;
                
            case 'v': // software version
                printf("ismtools v%s\n", version.c_str());
                printf("Giulio Formenti giulio.formenti@gmail.com\n");
                exit(0);
                
            case 'h': // help
                printf("ismtools [command]\n");
                printf("\nOptions:\n");
                printf("-v --version software version.\n");
                printf("--cmd print $0 to stdout.\n");
                exit(0);
        }
        
        if    (argc == 2 || // handle various cases in which the output should include summary stats
              (argc == 3 && pos_op == 2) ||
              (argc == 4 && pos_op == 3)) {
            
        }
        
    }
    
    if (cmd_flag) { // print command line
        for (unsigned short int arg_counter = 0; arg_counter < argc; arg_counter++) {
            printf("%s ", argv[arg_counter]);
        }
        printf("\n");
        
    }
    
//    std::string A = "CAGTCAGTAGTACGTACGaaTAGC";
//    std::string B = "CAGTCAGtgTAGTACGTACGTAGC";
    std::string A = "AAAAAAAATTAATAAAAAAAAACTAAAATAAAAAAATAAAAAAAAAATCAATAAAAAAAAATTAAAATAAAAAAATAA";
    std::string B = "AAAAATTAATAAAAAAAACTAAAATAAAAAAAAAAAAAAAAAATAAAAAAATCAATAAAAAAAATTAAAATAAAAAAAAAAAAAAAAAATAA";
    int8_t match_score = 1, mismatch_score = -1, gap_score = -1;
    int dp[MAX_N][MAX_N];
    
    ismtools(match_score, mismatch_score, gap_score, A, B, dp);
    
//    std::cout<<"Invoking: "<<cmd<<std::endl;
//    std::system(cmd.c_str());
    
    exit(EXIT_SUCCESS);
    
}
