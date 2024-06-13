echo "Enter string 1" 
read -a string1 
echo "Enter string 2" 
read -a string2 
if [ $string1 == $string2 ];  
then 
  echo "Strings are equal" 
else 
  echo "Strings are not equal" 
fi 
