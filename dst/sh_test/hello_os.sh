awk 'NR==8||NR==32||NR==128||NR==512||NR==1024{print}' $1 > $2
