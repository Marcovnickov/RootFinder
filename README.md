Se eligio la formula de Cardano sobre la resolucion por el metodo de Vieta, debido al problema de presicion del uso de funciones trigonometricas, y funciones hiperbolicas. 

Limitantes de la implementacion:

- Se espera que se manden los 4 coeficientes del polinomio de la forma Ax^3 + Bx^2 + Cx + D = 0, inclusive si el valor de algun coeficiente es cero
- Se espera que si se mandan numeros complejos, sean estos separados por una coma y sin espacio entre valores reales e imaginarios, por ejemplo: 
     3,5 representa el numero complejo 3 + 5i
- Se espera que los coeficientes que se dan sean numeros validos, de los contrario se considerara el coeficiente incorrecto dado, como el valor 0
- La impresion de las tres raices seran separadas por coma, por ejemplo para los coeficientes:
    A=1, B=2, C=3, D=4, el resultado impreso se vera de la siguiente forma: 
    {-1.65063, -0.174685+1.54687i, -0.174685-1.54687i}
- Si el valor del coeficiente A es igual a cero, se imprimira: { }
- Siempre se imprimiran las 3 raices inclusive si se repiten los valores de las raices, por ejemplo para los coeficientes:
    A=1, B=0, C=0, D=0, se imprimira: {0, 0, 0}
- Debido a que se aproxima la raiz cubica de un numero convirtiendo el numero complejo a forma polar:
   Z^(1/3) = r^(1/3)(cos( (theta + 2PI) / 3 ) + i*sen( (theta + 2PI) / 3 )  
   Donde:
   r     = Es el modulo del numero complejo
   theta = El angulo formado con el eje real del primer cuadrante
 
 Los valores de las raices cubicas pueden tener un error de aproximacion
