# sk

# 以下を実行
# g++ -DB_64 -I../include/ ../lib/BDD64.a zddtoknuth.cpp -o first
# g++ -DB_64 -I../include/ ../lib/BDD64.a zddpre.cpp -o second
# ./first <data/zddfile
# ./second | sort -r -n -k 2 | sort -r -n -k 1
