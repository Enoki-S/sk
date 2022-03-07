# sk

# mkdir name
# cd name
# git clone https://github.com/Shin-ichi-Minato/SAPPOROBDD
# git clone https://github.com/junkawahara/sbdd_helper
# git clone https://github.com/nttcslab-alg/d3x
# それぞれのreadmeを参照し準備．このとき，helperの位置，SAPPOROBDD/libのBDD64.aに注意
# cd SAPPOROBDD
# git clone https://github.com/Enoki-S/sk
# cd sk
# 以下を実行 先にfirstを実行し，
# g++ -DB_64 -I../include/ ../lib/BDD64.a zddtoknuth.cpp -o first
# ./first <../../d3x/data/zddfilename
# g++ -DB_64 -I../include/ ../lib/BDD64.a zddpre.cpp -o second
# ./second | sort -r -n -k 2 | sort -r -n -k 1
