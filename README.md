# cs221hw8. View in raw format.
To build, use make.
Design decisions. I decided to use chrono instead of time despite cpplint preferring time. I started using chrono and switched to time at the end. The random permutations only got smaller once or twice, which was really suspicious. I elected to just go back to what I was doing before.
test_cities was not required, but I made it anyway. Similarly, shortest.tsv and speed.tsv are not required, but they allow their respective gifs to be reproduced.