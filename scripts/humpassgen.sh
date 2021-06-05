if [ "$#" -ne 1 ];
then
  count=16
else
  count=$1
fi

rnddig $((count * 8)) | tr -d "\n " > temp

# array com codigos especiais
simb=("@" "$" "%" "&" "!" "#" "?" "~")
n_simb=8

for ((i=0 ; i < count ; i++)) do
  (  wordgen ;
      echo "_" ;
      wordgen ;
      echo ${simb[$RANDOM % $n_simb]} ;
      cut -c $((i*8 + 1))-$(((i+1)*8 + 1)) temp ) \
      | tr -d "\n " | cat
  echo ""
done

rm temp