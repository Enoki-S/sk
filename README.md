# sk

# mkdir name
# git clone https://github.com/Shin-ichi-Minato/SAPPOROBDD
# git clone https://github.com/junkawahara/sbdd_helper
# git clone https://github.com/nttcslab-alg/d3x
# cd SAPPOROBDD
# git clone https://github.com/Enoki-S/sk
# cd sk
# 以下を実行
# g++ -DB_64 -I../include/ ../lib/BDD64.a zddtoknuth.cpp -o first
# g++ -DB_64 -I../include/ ../lib/BDD64.a zddpre.cpp -o second
# ./first <data/zddfile
# ./second | sort -r -n -k 2 | sort -r -n -k 1
