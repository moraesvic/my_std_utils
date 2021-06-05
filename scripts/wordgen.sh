## requisito: dict-wn

if [ "$#" -ne 1 ];
then
  count=1
else
  count=$1
fi
shuf -n $count /usr/share/dict/american-english

