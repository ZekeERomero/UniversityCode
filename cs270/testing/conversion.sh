read -p "Enter mpg: " mpg

((e=1609))
((e=$e/378))
((e=$e*mpg))

echo $e
