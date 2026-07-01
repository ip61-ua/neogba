1 de julio.

# Marco teórico

La emulación es un ámbito informático que procura en la medida de lo posible imitar las instrucciones de una máquina en otra para la que hay fórmula fácil de ejecutarlas. Así es cómo podemos lograr ejecutar programas informáticos (software) antiguos para computadoras no recientes en la actualidad. De esta forma podemos disfrutar del software de cuyo hardware resulta de difícil obtención al alcance de los dispositivos actuales. La principal motivación de los programas emuladores son la preservación del software.

La Game Boy Advance es una videoconsola lanzada por la niponesa Nintendo a principios de los 2000 como sucesora de sus portátiles Game Boy. La familia de las portátiles Game Boy tuvo una gran aceptación el mercado por el asentamiento de sagas vídeojuegos reconocibles. En la actualidad ya no se produce este hardware, lo cual supone un reto para la preservación del software (y en concreto del videojuego). Sin un emulador que pudiese ejecutar programas de ese hardware, no sería fácil reproducir las experiencias originales. Obligando a recurrir a imitaciones, copias y recreaciones derivadas que introducen cambios o dificultan su acceso. Bajo esta utopía, para poder ejecutar programas antiguos hoy, tendríamos que constantemente reescribir todo software. Sin embargo, la emulación propone no imitar la programa sino la máquina donde corre. Debido a su popularidad y a la falta mantenimiento, esta línea de consolas se presta frecuentemente a la enseñanza o experimentación informática.

Al igual que cualquier programa informático, el emulador está compuesto instrucciones binarias y basadas en un código fuente legible por el programador. El código fuente es todo aquel recurso utilizado para generar el programa final. Así es que, un código fuente puede albergar archivos de texto, configuraciones, automatizaciones y multimedia necesaria. Rara vez es la que un programa no se escriba en un lenguaje de programación. A grandes rasgos, un lenguaje de programación es un conjunto de reglas sintácticas legibles por el humano que sirven para instruir el comportamiento de un hardware. Existen varias clasificaciones para categorizar lenguajes pero llamaremos a los lenguajes de bajo nivel aquellos con mayor acople al hardware como ensamblador de ARM y los de alto nivel que hagan lo contrario como C++. En función del lenguaje y su uso, puede requerir un transpilador, un compilador o un intérprete para preproceasar.

El desarrollo de un emulador implica conocer en profundidad la arquitectura hardware a la que se pretende emular. La GBA alterna entre dos en función del título a cargar. Esta generación sucesora introduce un procesador ARM. El fabricante ARM es uno de los más grandes y recurridos para los dispositivos portátiles como móviles cuotidianos. Los procesadores ARM han ganado la popularidad de hacer menor consumo energético frente a otros competidores. Tanto ARM como intel son marcas importantes para el desrrollo de arquitecturas hardware. En este sentido una arquitectura puede abargar la organización del hardware, conjunto de instrucciones y lógica booleana para la aritmética, tipos de datos y entre otras cuestiones...

También será necesario conocer cómo un software habitúa a ser configurado, alojado, gestionado en colaboración en línea a través de un gestor de versiones del programa como git. Este aspecto es vital para gran parte de emuladores porque suelen estar conformados por un equipos de entusiastas voluntarios a mejorar el programa emulador. En esta línea, cabe esperar conocimiento sobre licencia de software.

Los algoritmos son procedimientos que producen salidas con un mecanismo óptimo. Son fundamentales para cualquier programa serio y por tanto es recomendable conocer qué son, fórmulas, cómputo de complejidades. Aparntemenre que reusultan de interés para 

Para este trabajo es recomendable conocer los lenguajes de programación de escritorio y de bajo nivel como el lenguaje de programación C++, las arquitecturas de hardware en general y en concreto la arquitectura ARM, la lógica boleana, la videoconsola Game Boy Advance.

Guión
- motivación y objetivos. De donde sale la idea
- cómo edito, cómo documento, repo git, documentación.
- marco teórico: (gba, contexto), c++ (testing, editor, framework, biblioteca)
- c-style c++ implica limitarse -> pero idomatico hard -> transicion poco.
- decidí implementar extractores y constructores de instrucciones según docs.
- primero con macros pero endeble. luego templates mejor -> tests iban más rápido.
- registros -> ¿cómo es la estructura? -> ¿porque cambiarla? -> macros
- flags de registros -> lógica booleana implica conocer
- planteamiento inicial de métodos de cpu.
- las pruebas son vitales para comprobar que funciona sin tener un programa completo. -> detección de missspells -> util para comporbar que hace bien el cambio de modo.
- optimización de los switch
