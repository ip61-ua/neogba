Hasta 1 de julio.

# Marco teórico

La emulación es un ámbito informático que procura en la medida de lo posible imitar las instrucciones de una máquina en otra para la que hay fórmula fácil de ejecutarlas. Así es cómo podemos lograr ejecutar programas informáticos (software) antiguos para computadoras no recientes en la actualidad. De esta forma podemos disfrutar del software de cuyo hardware resulta de difícil obtención al alcance de los dispositivos actuales. La principal motivación de los programas emuladores son la preservación del software.

La Game Boy Advance es una videoconsola lanzada por la niponesa Nintendo a principios de los 2000 como sucesora de sus portátiles Game Boy. La familia de las portátiles Game Boy tuvo una gran aceptación el mercado por el asentamiento de sagas vídeojuegos reconocibles. En la actualidad ya no se produce este hardware, lo cual supone un reto para la preservación del software (y en concreto del videojuego). Sin un emulador que pudiese ejecutar programas de ese hardware, no sería fácil reproducir las experiencias originales. Obligando a recurrir a imitaciones, copias y recreaciones derivadas que introducen cambios o dificultan su acceso. Bajo esta utopía, para poder ejecutar programas antiguos hoy, tendríamos que constantemente reescribir todo software. Sin embargo, la emulación propone no imitar la programa sino la máquina donde corre. Debido a su popularidad y a la falta mantenimiento, esta línea de consolas se presta frecuentemente a la enseñanza o experimentación informática.
	
Al igual que cualquier programa informático, el emulador está compuesto instrucciones binarias y basadas en un código fuente legible por el programador. El código fuente es todo aquel recurso utilizado para generar el programa final. Así es que, un código fuente puede albergar archivos de texto, configuraciones, automatizaciones y multimedia necesaria. Rara vez es la que un programa no se escriba en un lenguaje de programación. A grandes rasgos, un lenguaje de programación es un conjunto de reglas sintácticas legibles por el humano que sirven para instruir el comportamiento de un hardware. Existen varias clasificaciones para categorizar lenguajes pero llamaremos a los lenguajes de bajo nivel aquellos con mayor acople al hardware como ensamblador de ARM y los de alto nivel que hagan lo contrario como C++. En función del lenguaje y su uso, puede requerir un transpilador, un compilador o un intérprete para preproceasar.

El desarrollo de un emulador implica conocer en profundidad la arquitectura hardware a la que se pretende emular. La GBA alterna entre dos en función del título a cargar. Esta generación sucesora introduce un procesador ARM. El fabricante ARM es uno de los más grandes y recurridos para los dispositivos portátiles como móviles cuotidianos. Los procesadores ARM han ganado la popularidad de hacer menor consumo energético frente a otros competidores. Tanto ARM como intel son marcas importantes para el desrrollo de arquitecturas hardware. En este sentido una arquitectura puede abargar la organización del hardware, conjunto de instrucciones y lógica booleana para la aritmética, tipos de datos y entre otras cuestiones... En concreto, el procesador ARM de la GBA es ARM7TDMI que implementa la 

También será necesario conocer cómo un software habitúa a ser configurado, alojado, gestionado en colaboración en línea a través de un gestor de versiones del programa como git. Este aspecto es vital para gran parte de emuladores porque suelen estar conformados por un equipos de entusiastas voluntarios a mejorar el programa emulador. En esta línea, cabe esperar conocimiento sobre licencia de software.

Los algoritmos son procedimientos que producen salidas a cambio de entradas siguiendo una serie de instrucciones. Son fundamentales para cualquier programa serio y por tanto es recomendable conocer qué son, fórmulas, y el cómputo de complejidades por encima.

Para este trabajo es recomendable conocer los lenguajes de programación de escritorio y de bajo nivel como el lenguaje de programación C++, las arquitecturas de hardware en general y en concreto la arquitectura ARM, la lógica boleana, la videoconsola Game Boy Advance.

# Motivación

La idea de hacer un emulador siempre ha estado ahí desde que he empezado a usarlos. Pensar que algo que requiera técnica pudiese ser divertido de aprender y examinar. Preguntándome cómo se hacen realmente. Hace cuatro años esta idea empezaba como una broma. Sin embargo, cuando me puse a plantear qué ideas hacer la única que vino es la implementar un emulador. En ese punto me quité de la cabeza sobre que fuera una broma y lo consideré como algo serio. El emulador es una pieza que opera a bajo nivel de los ordenadores que siempre me hubiese gustado tratar en algo más en profundidad en la carrera. Además, creo que este TFG puede ser destacado en un CV fácilmente. No todos los días (y más hoy) que haya tocado fundamentos a tan bajo nivel. Pues su realización implica investigación sobre una máquina ya descatalogada e implementación de la especificación de muchas fuentes. Y por supuesto, la optimización de los recursos. 

El objetivo último de este trabajo es aprender. No es el de competir frente a programas ya bien establecidos y con años de experiencia en este ámbito. Sino el planteamiento de este TFG como un reto. No busco reinventar la rueda sino conocerla más a fondo en este símil.

# Estado del arte

En contrucción... ¿Qué contar aquí?

- la arquitectura chip-8 es muy típica para prácticar emulación.
- la gba se presta a educación -> fundamentos -> ensamblador.
- mgba, libreto, https://emulation.gametechwiki.com/index.php/Game_Boy_Advance_emulators y licencias.
- legalidad -> roms, recrear, preservación, piratería.
- caso de uso -> depuración, pruebas, enseñanza.

# Metodología

Vamos a utilizar git como gestor de versiones del proyecto y github como alojamiento del proyecto. Aplicándose también para la memoria. De forma que el tutor pueda acceder cómodamente al trabajo realizado. La memoria es una plantilla de TFG recomendada por la EPS que emplea latex y su compilación a PDF es realizada a través de github actions, localmente o por una imagen Docker que incluye lo necesario para su compilación.

Voy a utilizar el editor de texto GNU Emacs para la programación en c++ así como para la documentación en latex y anotaciones en markdown con sus debidos paquetes para extender funcionalidades a este programa. A la hora de implementar cierta funcionalidad lo haré teniendo de un lado un archivo para ir anotando los pequeños avances que realice durante la sesión. Tengo configurado el editor de tal forma que fuese lo menos necesario salir de este para la realización de mis tareas. De forma que mientras programo puedo escuchar la radio de música, visualizar con un filtro del tema que uso la documentación en PDF a implementar, utilizar un frontend para manejar repositorios git, programar en c++, compilo el programa y pasarle las pruebas mientras hago anotaciones en markdown. Esto es genial para minimizar la fricción del uso y unificarlo utilizando atajos de teclado similares sin salir de la aplicaciones.

Al cabo de varias notas acumuladas, se pasa a la memoria donde se reordeordena y se corrigen faltan. Además de expandir o simplificar el texto según sea el caso y añadir referencias, formato...

El flujo de trabajo para la implementación del emulador consiste en: primero, determinar qué implementar; segundo investigar las especificaciones y restricciones que puedan afectar; tercero, implementar versión naive y experimentación; en cuarto lugar, escribir pruebas para automatizar y garantizar un mínimo funcionamiento y búsqueda de errores; y por útimo, refactoriazar y optimizar. Mientras tanto ir anotando los apartados que considero de revelante interés para la memoria tales como una explicación lo qué he hecho, comparativas entre diferentes versiones, justificación de la aplicación de buenas prácticas. Es siempre preferible escribir test porque automatizan la labor de comprobación del programa sin tener una versión completa del mismo. No obstante, para una mayor profundidad en la inspección del funcinamiento del programa, se recurre al frontend depurador a través de línea de comandos para el acotamiento de fallos.

El código fuente del emulador está escrito en el estándar C++26. A través del uso clangd podemos recibir en el editor de preferencia ayuda y sugerencias estáticas sobre nuestro código. Útil para la prevención de errores. Para las pruebas automatizadas, el proyecto hace uso del framework Google Test. Se ha preferido una simple construcción del proyecto con reglas escritas directamente para make inicialmente con tal de tener ya algo que se pueda ejecutar y probar desde el día uno. En un futuro con tal de extender su portabilidad, se podría implantar un metagenerador de proyectos para ajustarse mejor a la realidad de la programación en C++. Cabe recalcar que el código es automáticamente estilado por otra de las herramientas de clang para seguir en todos el mismo estilo y formato fuente. Siendo estas recomendaciones las de LLVM por su cercanía con el estilo de progrmación en lenguajes modernos. Al estar programando en C++ definiremos que los archivos de cabecera con la extensión hpp y los de implementación cpp.

A la hora de subir los cambios del emulador, el mensaje de confirmación de git será en inglés y prefijado con una abreviatura del tipo de cambio efectuado (refactorización, nuevas funcionalidades, documentación, arreglos...). 

Para la comunicación con el tutor se hace uso de reuniones presenciales, mensajería por correo electrónico, y asignación de fechas por Google Calendar.

# Implementación

## Trabajo previo

Antes de empezar el trabajo en serio, empecé una implementación de prueba. Aquella versión preliminar tenía como objeto de estudiar la viabilidad de la realización del TFG y predendía seguir uns prácticas idomáticas del lenguaje C++. Todo ello mientras me familiarizaba con la forma de realizar las pruebas con el framework y a investigar sobre la consola. En concreto el objetivo fue la implementación de una instrucción que sumara dos números. Ello suponía antes tener toda una infraestructura: Métodos y propiedades de la CPU, bus de memoria y la memoria. Aunque logré que realizara la suma lo cierto es que el código resulte dejaba mucho que desear. Las refactorizaciones al programa eran engorrosas y las prácticas idiomáticas dificultaban la lectura y entendimiento del programa. La lección que aprendí de este experimento es que aplicar los típicos hábitos de programación de alto nivel a uno más bajo era contraproducente. En un emulador buscamos escribir menos y muy óptimo, y evitar la sobrecarga de boilerplate. Por ejemplo, considerar cada registro como una clase o encapsular cada tipo de instrucción como una clase. En este último ejemplo es más propicia a errores. Despachar según el tipo de instrucción y no en instrucción concreta tiene un coste importante dado las pocas optimizaciones que se le puede aplicar. En el prototipo preeliminar definí una clase por cada tipo de instrucción, y que luego esa clase era la encargada de averiguar qué tipo de instrucción era exactamente. Sumado a otros métodos auxiliares de construcción y depuración implicaba para una clase asumir demasiadas responsabilidades. Otra de las cuestiones que motivaron al cambio fue la lentitud de los test que justificaban las pésimas decisiones de optimización. 

Pese a las dificultades, logré implementar una RAM de ejemplo y bus de memoria siguiendo la filosofía de POO. No fue tan costoso de seguir. Esta parte era bastante susceptible de ser implementada de esta forma. Pero sin embargo se notaba cómo un hack al tener que la memoria manejar información sobre sí misma en el bus... Una de las características que fueron curiosas de implementar es la memoria espejo. Siendo que en la memoria persistía una lista y daba igual la dirección de memoria socitada a acceder/modificar que involucraba al mismo offset.

Estos golpes de realidad motivaron a realizar importantes simplificaciones para centrarse más en mejoras que en escribir el código. Llegando averiguar más sobre cómo los emuladores de GBA dispachan la instrucción que toca de formas más óptimas usando tablas LUT frente a bloques switch. Y en paralelo, averiguar un algoritmo para rellenado de esta tabla.

El rumbo era el mismo pero el camino había cambiado. Ante el desconocimiento del gran repertorio de características del lenguaje hacía lento y complicado avanzar, opté por crear una versión lo más naive que, con el paso del tiempo, actualizaría para garantizar una mejor legibilidad de código y prácticas idiomáticas.

Lo primero que implementé fue una estructura básica de la cpu de ARM7TMI como un dos arreglos. Uno era una lista fija con todo el espacio necesario para albergar los 37 registros necesarios en total. Y la segunda servía para indicar cuales de estos registro utilizar. En otras palabras, esta segunda lista contiene solo los índices de los registros que se pudiesen precisar en ese modo. Otra de las implementaciones para este caso fue hacerlo sin la segunda lista y proporcionando un método que computará el índice del registro a interactuar. El problema era hacerlo de este modo resultaba muy complicado y surgían muchos condicionantes a evaluar. Dicho lo cual ralentizaba el rendimiento con branch misprediction (predicción de saltos) de los ordenadores modernos. Este suceso si bien no copiaba listas en listas daba pie a un problema todavía mayor: la falta de predicción y a una gran complejidad ciclomática por cada instrucción. En ese sentido esta implementación es peor porque realiza muchas operaciones por cada vez que nos refiramos a registros, mermando a así el rendimiento. Pudiendo haber 3 registros involucrados, lo cual carece de eficiencia al repetirse el mismo proceso eficiente. En consecuencia, la primera implementación es más oficiente porque en caso de hacerse el cambio de modalidad arm, solo se hace una copia de una lista de elementos que sí sabemos qué son a simple vista. Además esta copia lista a la lista índices actual se hace una vez y solo cuando se pida el cambio de modo. Que resulta en una menor frecuencia que la manipulación de registros.

A continuación añadí algunos métodos para una fácil lectura y escritura del código para la manipulación de registros. Para decir que registros estaban en qué modos del procesador utilicé macros. Las macros son un mecanismo heredado de C para copiar y pegar texto del código fuente mecanismo que más tarde sería remplazado por otro con seguridad de tipos y restricciones. 

Antes de proceder con la reescritura, decidí por implementar siguiendo la documentación los tipos las intrucciones. Aquí el enfoque sería complemente diferente: no hay clases solo funciones auxiliares para el conjunto del set de instrucciones. De modo que si una instrucción necesitase extraer/establecer unos campos o ignorar otros lo pudiese decidir y operando sobre el bits de las instrucción. El problema era poner en marcha este planteamiento porque requiere crear demasiadas funciones muy similares entre sí. Casi siempre son las mismas operaciones con datos de entradas de diferentes. A menudo, plantarse un número prohibitivamente grande de operaciones muy similares entre sí sugiere utilizar algún tipo de metaprogramación con tal de mejorar la mantenibilidad en el futuro y reducir la tasa de error al codificar estos casos. Al igual en el anterior párrafo hice uso de las macros para generar las funciones. Cosa que posteriormente resultó en una refactorización con las plantillas.

Las templates son un recurso de metaprogramación que son evaluados en tiempo de compilación que fueron introducidos en c++. La ventaja de esta característica integrada es una mejor integración con el código respetando el tipado estático. El remplazo de macros por las templates resulto en una mejora de tiempos en las pruebas.

Algunos de los registros son para el acceso a los registros del modo actual, acceder al contador del programa, método para cambio modo y actualizar todo lo necesario de la estructura de la cpu. Los métodos estan en su mayoría están pensados para usarse con lógica boleana así como operadores ~ & | ^ para una mayor flexibilidad de manipulación. Es el ejemplo para la lectura y escritura del registro cpsr. 

En cualquier caso, las pruebas automatizadas han tomado un papel fundamental para ir construyendo un programa paso a paso, comprobando que las cosas funcionen y no haya ninguna letra mal puesta o algo que no esté en su sitio. 

Luego de realizar los cambios, me puse a analizar el método que hace cambia de modo. Resulta que existe toda una ciencia detrás de las optimizaciones del compilador. GCC y CLANG son los dos compiladores más establecidos en el entorno de desarrollo de C++. Y hay que tener en cuenta que no todos producen el mismo binario dado un mismo código fuente. Por ello interesante ver el comportamiento y las optimizaciones aplicadas por distintos comportamientos. Pequeños cambios como pasar de usar un tipo de 64 bits a uno 8 bits puede afectar al rendimiento. 

El método a analizar estaba implementado por medio de un bloque switch y para caso un return del índice de la lista activa por la que cambiar. Pese a que pueda ser una buena idea, realmente el binario obtenido de un compilador u otro. Pudiendo resultar en una especie de LUT o condicionales consecutivas. Para ambas compativas y usando el -O3, GCC ha detectado un patrón y ha transformado el bloque switch tabla de búsqueda a difrencia que clang que dada con una tabla de satos. La versión obtenida por GCC tiene solo un salto condicional. La refactorización que se propone es aprovecharse de la operación de bits para construir el índice de forma que se suma tomando los dos primeros y los dos siguientes desplazados a la derecha a 2. Pero antes si el modo de sistema solicitado es el de sistema devolver inmediato directamente. En consecuencia, logramos una versión con menos restricciones en la es más suceptible a ser mejorada por el compilador. GCC emplea una instrucción cmove encarga en sobreescribir el resultado con 1 si la comparación es igual a 31 (0b11111).

La página godbolt lo pone sencillo para la inspección del ensablador pudiendo combinar flags, compilador y máquina objetivo. Este tipo de prácticas resultan siempre interesantes tratar puesto que cambios simple pueden mejorar la eficiencia del programa. Además notar los cambios en el binario producido por cada campilador y/o cambio en el sistema.

# 2 de julio 

¿qué voy a hacer?
- quitar macros por std::arrays en las instrucciones. (hecho)
  - Por el mismo motivo de siempre, #STOPMACROS.
  - pueden ser evaluadas en tiempo de compilación. 
  - CAMBIOS:
    - Manejo de memoria más simple, sin necesidad de copiar
	- Asignación o fill.
	- complicación en los test -> resuelta con un for mejor.
	- ahora ocupa un registro menos (es fíctício el spsr, por que no está en usr ni sys)
	- reducción de tamaño en uno -> mejor provecho de espacio
	- tarda más con std::array (pasando de 8 a 11 segundos)
    - no puede ser porque array es 0-cost abstraction
	- lo que está pasando es que tarda por que gtest tiene una impresora al comparar arrays que lo ralentiza.
	- si los test son muy lentos, considerar valorar esto assert_true == o recuperar el método de memcmp que había antes par comparar.

- Añadir métodos de lectura y escritura de calquier registro. (mu facil)

# 3 de julio

¿qué voy a hacer?
- me he pasado a un ordenador de torre con debian donde puedo seguir trabanjando con mi metodología con el añadido de verlo en pantalla grande para los errores de c++ (lol).
- implementar instrucciones aritméticas.
  - ADC Add with carry Rd := Rn + Op2 + Carry
  - ADD Add Rd := Rn + Op2
  - AND AND Rd := Rn & Op2 
  - BIC Bit Clear Rd := Rn & ~ Op2 
  - CMN Compare Negative CPSR flags := Rn + Op2
  - CMP Compare CPSR flags := Rn - Op2
  - EOR Exclusive OR Rd := (Rn AND NOT Op2) OR (op2 AND NOT Rn)
  - MOV Move register or constant Rd : = Op2
  - MVN Move negative register Rd := 0xFFFFFFFF EOR Op2
  - ORR OR Rd := Rn OR Op2 
  - RSB Reverse Subtract Rd := Op2 - Rn 
  - RSC Reverse Subtract with Carry Rd := Op2 - Rn - 1 + Carry 
  - SBC Subtract with Carry Rd := Rn - Op2 - 1 + Carry
  - SUB Subtract Rd := Rn - Op2
  - TEQ Test bitwise equality CPSR flags := Rn EOR Op2 
  - TST Test bits CPSR flags := Rn AND Op2

  - ESTOY ENCRONTRANDO DISCREPANCIAS EN LA DOCUMENTACIÓN
  - me he puesto a hacer and
  - he decidido añadir un bit i en fsr.
  - https://iitd-plos.github.io/col718/ref/arm-instructionset.pdf
  - complicación porque hay que anidar mucho o muchas funciones repetidas.
  - lo voy a hacer full naive que posteriormente usar templates o algo para mejorar el código. 
  - operand2 tiene dos formas de operar en función del bit i
    - o es un registro con shift (tipo de shift determinado)
	- o un inmediato rotado por dos
	- por lo tanto operand2 como tal no existe
	- hay casos especiales
	- he tenido que añadir más extractores
	- Operand2 es muy complicado pero es común a todos los data procesing por igual
	- me pongo a hacer una prueba
	- tanto tiempo programando tengo la cabeza como un platillo y no me doy cuenta de que hay que inicializar registro lol.
	- la funcion amr_and funciona pero creo que como vamos a trabajar con lut vamos a necesitar con muchas versiones de modo que quitaremos ifs y ramas incesesarias y utilicemos ifs.
	- la custión aquí es como hacerlo "modular". Según he estado investigando el equipo de mgba lo que hace es construir por partes usando macros. Digamos hay una versión con al S activa y otra sin activar, otra usando el campo operand2 que toca directamente.
	- Este es idóneo al que provecharse. No obstante, hay partes que dependen de como haya ido la anterior. 
	- Recordar que la idea es crear alto rendimiento para hacerlo más realista.
	- Creo que es posible hacer algo así en c++ idomático. En donde realmente lo cambia es en sí el manejo de la operación en sí. (Bueno aunque operand2 tiene su telita) pero es un proceso muy mecánico que siempre será el mismo y lo más importane que tendrá el mismo resultado, sacar un número de operand2 del que podemos operar. Aunque hay caveats porque si el flag s está activo implica actualizar el registro en base a lo ocurrido en la ejecución.
    - por qué he puesto fuera las instrucciones? por no engrasar tanto a la estructura del arm7tdmi	
  - He cambiado el obtenedor de conjuntos de registros de usar una condicional a usar la operación módulo.

# 7 de julio

- La mayor penalización en un emulador es el if.
- La idea cómo construir la LUT es hacerla de tal forma que eliminemos lógica condicional y la remplacemos por la lógica aritmética.
- En bruto, nuestro objetivo es eliminar el típico código if (true) algo.
- Algunas de las opciones barajadas:
  0. Dejarlo con las condicionales. -> Penalización extrema
  1. Escribir a mano todas las combinaciones. Lo cual da bastante puede dar pie a errores tipográfico y código poco de reusable.
  2. Algún mecanismo de metaporgación de plantilla. No me cuadra ninguna cabida de implementación por su rigidez. Este es la solcuión utilizada en mgba con macros bajo c. Lo cual resulta bastante práctico y flexible a prestarse a este tipo de situaciones.
  
  el código inicial es 
  
  ``` c++
  
void neogba::arm_AND(arm7tdmi* cpu, u32 inst) {
  u32 shift_amount, imm, rm, operable_operand2{};

  u8 rn_idx{ISA_ARM_FSR_RN::get(inst)};
  u8 rd_idx{ISA_ARM_FSR_RD::get(inst)};
  u8 shift_type, rm_idx;

  bool i{ISA_ARM_FSR_I::get(inst)};
  [[maybe_unused]] bool s{ISA_ARM_FSR_S::get(inst)};
  bool four, is_special_case;

  if (i) {

    // operand2 is immediate value with shift.

    shift_amount = 2 * ISA_ARM_FSR_OPERAND2_ROTATE::get(inst);
    imm = ISA_ARM_FSR_OPERAND2_IMM::get(inst);

    operable_operand2 =
        (shift_amount == 0) ? imm : ((imm >> shift_amount) | (imm << (32 - shift_amount)));
  } else {

    // operand2 is a register with shift.

    rm_idx = ISA_ARM_FSR_OPERAND2_RM::get(inst);
    rm = cpu->read_active_register(rm_idx);
    shift_type = ISA_ARM_FSR_OPERAND2_SHIFT_TYPE::get(inst);
    four = ISA_ARM_FSR_OPERAND2_4::get(inst);

    shift_amount = four ? cpu->read_active_register(ISA_ARM_FSR_OPERAND2_RS::get(inst))
                        : ISA_ARM_FSR_OPERAND2_SHIFT_AMOU::get(inst);

    is_special_case = !four && shift_amount == 0;

    switch (shift_type) {

    case LSL:
      if (is_special_case) {
        operable_operand2 = rm; // LSL #0
      } else {
        operable_operand2 = (shift_amount >= 32) ? 0 : (rm << shift_amount);
      }
      break;

    case LSR:
      if (is_special_case)
        shift_amount = 32; // LSR #0

      operable_operand2 = (shift_amount >= 32) ? 0 : (rm >> shift_amount);
      break;

    case ASR:
      if (is_special_case)
        shift_amount = 32; // ASR #0

      if (shift_amount >= 32) {
        // Shifting ge 32, a. if and negative -> ffff, b. if and postive -> 0s
        operable_operand2 = (rm & 0x80000000) ? 0xffffffff : 0;
      } else {
        // Preserve sign bit with i32
        operable_operand2 = static_cast<u32>(static_cast<int32_t>(rm) >> shift_amount);
      }
      break;

    case ROR:
      if (is_special_case) {
        // RRX: Rotate 1 bit and include Cin.
        if (cpu->is_cpsr(arm7tdmi::C, arm7tdmi::C))
          operable_operand2 = 0x80000000;

        operable_operand2 |= (rm >> 1);
      } else {
        shift_amount %= 32; // 32 = 64 -> rotate 0 bits
        operable_operand2 =
            (shift_amount == 0) ? rm : ((rm >> shift_amount) | (rm << (32 - shift_amount)));
      }
      break;
    }
  }

  u32 res = cpu->read_active_register(rn_idx) & operable_operand2;

  cpu->write_active_register(rd_idx, res);

  if (s)
    cpu->set_cpsr(arm7tdmi::Z | arm7tdmi::N | arm7tdmi::C | arm7tdmi::V,
                  (res == 0 ? arm7tdmi::Z : 0) | (((res & 0x8000000) != 0) ? arm7tdmi::N : 0));
}
  ```

Y la idea es ir modularizarla. 

- La primera refactorización consistirá en homogenizar el cómputo de operand2 puesto será una cuestión recurrente en operaciones de este tipo. 
  - Para esto vamos llevarnos a funcionalidad aparte. Al estar todo junto, como típica replicación, debemos refactorizar para ver qué trasladar.
  - Ahora queda mucho más claro que hay que pasar por computar operand2 obligatoriamente.
  
  ``` c++
  #include "neogba/arm7tdmi/arm_isa.hpp"

using namespace neogba;

neogba::arm_operand2_result neogba::arm_operand2_compute(arm7tdmi* cpu, u32 inst) {
  u32 shift_amount, imm, rm, operable_operand2{};
  u8 shift_type, rm_idx;

  bool i{ISA_ARM_FSR_I::get(inst)};
  bool four, is_special_case;

  if (i) {

    // operand2 is immediate value with shift.

    shift_amount = 2 * ISA_ARM_FSR_OPERAND2_ROTATE::get(inst);
    imm = ISA_ARM_FSR_OPERAND2_IMM::get(inst);

    operable_operand2 =
        (shift_amount == 0) ? imm : ((imm >> shift_amount) | (imm << (32 - shift_amount)));
  } else {

    // operand2 is a register with shift.

    rm_idx = ISA_ARM_FSR_OPERAND2_RM::get(inst);
    rm = cpu->read_active_register(rm_idx);
    shift_type = ISA_ARM_FSR_OPERAND2_SHIFT_TYPE::get(inst);
    four = ISA_ARM_FSR_OPERAND2_4::get(inst);

    shift_amount = four ? cpu->read_active_register(ISA_ARM_FSR_OPERAND2_RS::get(inst))
                        : ISA_ARM_FSR_OPERAND2_SHIFT_AMOU::get(inst);

    is_special_case = !four && shift_amount == 0;

    switch (shift_type) {

    case LSL:
      if (is_special_case) {
        operable_operand2 = rm; // LSL #0
      } else {
        operable_operand2 = (shift_amount >= 32) ? 0 : (rm << shift_amount);
      }
      break;

    case LSR:
      if (is_special_case)
        shift_amount = 32; // LSR #0

      operable_operand2 = (shift_amount >= 32) ? 0 : (rm >> shift_amount);
      break;

    case ASR:
      if (is_special_case)
        shift_amount = 32; // ASR #0

      if (shift_amount >= 32) {
        // Shifting ge 32, a. if and negative -> ffff, b. if and postive -> 0s
        operable_operand2 = (rm & 0x80000000) ? 0xffffffff : 0;
      } else {
        // Preserve sign bit with i32
        operable_operand2 = static_cast<u32>(static_cast<int32_t>(rm) >> shift_amount);
      }
      break;

    case ROR:
      if (is_special_case) {
        // RRX: Rotate 1 bit and include Cin.
        if (cpu->is_cpsr(arm7tdmi::C, arm7tdmi::C))
          operable_operand2 = 0x80000000;

        operable_operand2 |= (rm >> 1);
      } else {
        shift_amount %= 32; // 32 = 64 -> rotate 0 bits
        operable_operand2 =
            (shift_amount == 0) ? rm : ((rm >> shift_amount) | (rm << (32 - shift_amount)));
      }
      break;
    }
  }

  return {shift_amount, operable_operand2};
}

void neogba::arm_AND(arm7tdmi* cpu, u32 inst) {
  // u32 operable_operand2{};

  u8 rn_idx{ISA_ARM_FSR_RN::get(inst)};
  u8 rd_idx{ISA_ARM_FSR_RD::get(inst)};

  [[maybe_unused]] bool s{ISA_ARM_FSR_S::get(inst)};

  auto result{neogba::arm_operand2_compute(cpu, inst)};

  u32 res = cpu->read_active_register(rn_idx) & result.operable_operand2;

  cpu->write_active_register(rd_idx, res);

  if (s)
    cpu->set_cpsr(arm7tdmi::Z | arm7tdmi::N | arm7tdmi::C | arm7tdmi::V,
                  (res == 0 ? arm7tdmi::Z : 0) | (((res & 0x8000000) != 0) ? arm7tdmi::N : 0));
}
  ```

  - con esto en mente, lo que podemos hacer es otra optimización al código de obtención del valor a operar de operand2, es crear una pequeña tabla lut cogiendo y tomando valores de interés. En otras palabras, vamos a aprovecharnos de la abstracción de los extractores para realocar a nuestra conveniencia e interés un código personalizado que sirva a modo de índice para ubicar la operación concreta a realizar. Esto es plausible debido a la muy definida funcionalidad y acotada combinación. Para he esto he hecho explícito un método para devolver u8 en los extractores del estilo isa_bool.
  - NO NO LO VEO.
  
  
8 de julio

Creo que es necesaria la abstracción de lut. Mucho hablar teoricamente y pero poca prácticticidad.

``` c++

template <std::size_t max_lenght, typename store_t = void*, typename idx_t = neogba::u8,
          typename return_t = void>
struct lut {
private:
  std::array<store_t, max_lenght> storage;

public:
  virtual std::size_t norm_idx(idx_t idx) const;

  store_t get(idx_t idx) const;
  return_t run(idx_t idx, ...) const;

  void put(idx_t idx, store_t what);
  void fill(idx_t idx_base, store_t what, idx_t mask);

  void erase(idx_t idx);

  bool is_empty() const;
  bool is_empty(idx_t idx) const;

  std::size_t length() const;
  std::size_t count_stored(store_t what) const;
};

```

- Me he dado cuenta que un plantilla no debería ir en un archivo separado
- lo he juntado todo.
- he hecho todo a tiempo de compilación.


``` c++
template <std::size_t max_length, typename store_t = void*, typename idx_t = u8,
          typename return_t = void>
class lut {
private:
  std::array<store_t, max_length> storage{};
  constexpr void put(std::size_t raw_idx, store_t what) { storage[raw_idx] = what; }
  constexpr std::size_t fill_recursive(std::size_t base, std::size_t mask, store_t what, bool high,
                                       std::size_t bit = 0) {
    // caso base
    std::size_t shifted{mask >> bit};
    if (shifted == 0)
      return 0;

    // caso recursivo no fork
    bool is_mask_one{(shifted & 0x1u) == 1};
    if (!is_mask_one)
      return fill_recursive(base, mask, what, high, ++bit);

    // caso recursivo branch
    std::size_t exclusive_mask_bit{1u << bit}, exclusive_base_bit{base & (exclusive_mask_bit)};
    bool is_base_zero{exclusive_base_bit == 0}, is_base_one{not is_base_zero}, low{not high};
    u8 count{0};

    if ((high and is_base_zero) or (low and is_base_one)) {
      count = 1;
      base ^= exclusive_base_bit;
    }

    ++bit;

    return count + fill_recursive(base, mask, what, true, bit) +
           fill_recursive(base, mask, what, false, bit);
  }

public:
  constexpr virtual std::size_t norm_idx(idx_t idx) const { return static_cast<std::size_t>(idx); }

  constexpr store_t get(idx_t idx) const { return storage[norm_idx(idx)]; }
  constexpr return_t run(idx_t idx, auto... params) const { return get(idx)(params...); }

  constexpr void fill(idx_t idx, store_t what) { storage[norm_idx(idx)] = what; }
  constexpr std::size_t fill(idx_t idx_base, store_t what, idx_t mask) {
    std::size_t b{norm_idx(idx_base)}, m{norm_idx(mask)};

    return fill_recursive(b, m, what, true) + fill_recursive(b, m, what, false);
  }

  constexpr std::size_t length() const { return max_length; };
  constexpr std::size_t count_stored(store_t what) const {
    std::size_t n{};
    for (auto elem : storage)
      if (elem == what)
        n++;
    return n;
  }
};
```

  - Luego me puse a refactorizar el código para una versión branchless el caso de recursivo branch.
  - Pero no tuvo tanto sentido, porque no cubiría la llamada a función
  - Además esto tiene penalización en tiempo de compilación y no en ejecución preferiblemente. O en caso de tenerlo, sería mínimo en ejecución por la naturaleza de la estructura.
  - Vale, me estoy liando. Vamos a hacer naive en caso recursivo branch para ir pasando los test y optimizando. O no porque a quién le importa si es solo una vez.
  - vale ya se lo que estaba pasando y es que el test estaba mal. No seguía la signatura bien. He simplificado lógica.
  - ES MUY IMPORTANTE DEPURAR ANTES QUE HACER PRINTS.
  - mE HE PUESTO AHORA con intentar añadir funciones a la lut. Por que esto es lo deseable, definir un conjunto de operaciones finitas que puedan ser llamadas con similar signatura.
  - A la hora de utilizar funciones el lenguaje emplea todo un sistema moderno funcional. Creamos signatura de función con using.
  - Los lambdas con funciones anónimas y en la actualidad el estándar del c++ da demasiadas oportunidades para usarlas incluso en plantillas.
  - Para garantizar que las pruebas vamos a utilizar lambas que alteres variables del test. Lo cierto es que hay varios tipos de lambdas. Una es preservando con capturas referencias locales de ámbito, pero ello pierde ser una función típica. Es decir deja de ser un puntero crudo como sí pasa en c.
  - interesa hacer un test fácil, comprobar que realmente se ha llamado. Y esto es más típico de mocks en donde comprobamos de forma unitaria a llamada a una dependencia externa falsificando su comportamiento y retorno para registrar que tal llamada sí fue efectiva. sin embargo, vamos a hacer algo más simple y es comprobar que unos valores externos hayan sido modificados.
  - sin embargo, gtest trae un framwwork para mocking.
  - HACER EXPECT CALL.... un poco más enrevisada la sintaxis no es tan directa como en otros frameworks como easy mock en java.
  
# 9 de julio

  - he añadido más test para comprobar cómo usar la lut.
  - he optimizado algunas cosas más. como reemplazar la operación módulo por una máscara.
  - Hay un problema en el método run y es que el reenvío de parámetros a sus repectivas funciones, las copia y no preserva referencias.
  - para solucionar esto debemos utilizar la referencia universal auto&&... params para tratar todos los tipos lvalue o rvalues o mantener de solo lectura. 
  - std::forward<decltype(params)> reenvia y mantiene la naturaleza de todos los tipos empaquetados en params mientras interfamente se trate como lvalue en el ámbido de run. Aunque viene a mantener soluciones recientes de c++ de movimiento.
  - Las llamadas virtuales tienen un coste a asumir. Añaden overhead de indirección.
  - por ello, he replanteado que en lugar de utilizar la derivación de la clase lut, he utilizado la inyección de políticas. Esto es que, hay un parámetro de plantilla que dicta el comportamiento de la lut. De modo que no permita cambio en tiempo de ejecución. Esto adelanta lo máximo posible al tiempo de compilación.
  - Beneficiándose de mayor flexibilidad.
  
  - Ahora que tenemos todo esto funcionando... ¿para qué?
    - bien, creo que es haber tocado esta estructura antes podemos hacernos a la idea los problemas y usabilidad de la misma.
	- métafora: la lut = multiplexor. En el fondo, eficiencia de una estructura depende fuertemente del uso que se le vaya a propiciar.
	- ! all struct are =
	- si pensamos a nivel de hardware, el multiplexor es una estructura perfecta para la búsqueda. Por que es directa!!!
	- Sabe exactamente donde hay un ítem o qué salida dar. O si hay varias que emitan la misma salida.
	- los multiplexores tienen una longitud fija. A no ser que interconectemos uno con otro.
	- lo que buscamos es una abstracción de coste cero que pueda ser ahustada a nuestras necesidades usando plantillas.
	- la lut no es más que un array "vitaminado" con métodos para poner más fácil inserción de elementos y también utilizar un código que sirva a modo índice con el navegar entre opciones. Pero el código que se use puede ser otro al que realmente se utilice. Dejando a conveniencia bien devolver 42, o un número aleatorio, o desaprovechar las entradas de la lut, o idílicamente aprochear para recortar y ajustar los bits de interés de la máscara.
	- otro caso de uso al que se le puede prestar esta implementación es al direccionamiento de memoria. Decidir a qué chip consultar.

  - Así retomando la especificación del cómputo de operand2 podemos ponernos a analizar como aplicarlo al cómputo de operand2.
  - Lo debamos hacer ahora es ver cómo podemos unificar todos las distintas combinaciones.
  - De una operación de procesado de datos y fsr nos interesa conocer su bit i y el campo operand2. Ya ha pasado un tiempo en el que no no acuerdo bien cuales ni cuántos eran. Pero los podemos construir utilizando los extractores.
  - Yo haría la lut tabla basándome en cómo esta hecha la implementación de operand2. 
  - De manera que es un método muy estúpido y mecánico en el explorar en orden las conexiones y bifurcaciones del código.
    1. siendo el bit i el más condicionante en la decisión.
	2. dentro de i = true, shift_amount es un condicionante porque dicta si devolver solo imm o realizar operación de encadenamiento y desplazo.
	
	- Por lo tanto tenemos que 
	  
	  ``` 
	  (lenguaje lógico)
	  shift_amount = rotate == 0
	  
	  i ^ shift_a  -> imm
	  i ^ -shift_a -> ((imm >> shift_amount) | (imm << (32 - shift_amount)))
	  ```

    3. Ahora si el i no es true, vamos a otra parte del código en la que se asume que "operand2 is a register with shift", y es algo más complidaca.
	4. el bit 4 nos dice si es otro registro o es shift_amount. En parte del código donde es realmente dificil hacer una inspección, podemos aplicar otro método y este consiste en ir del final al principio. Siendo que primero tomemos las sentencias finales y visualicemos qué ha hecho falta para llegar a ellas.

	- Por lo tanto tenemos que 
	  
	  ``` 
	  (lenguaje lógico)
	  -i ^ lsl ^ special_case                       -> rm
	  -i ^ lsl ^ -special_case ^ (shift_a >= 32)    -> 0
	  -i ^ lsl ^ -special_case ^ -(shift_a >= 32)   -> rm << shift_a
	  -i ^ lsr ^ special_case                       -> (shift_a = 32) // dejar e ir 
	  -i ^ lsr ^ (shift_a >= 32)                    -> 0
	  -i ^ lsr ^ -(shift_a >= 32)                   -> rm >> shift_a
	  -i ^ asr ^ special_case                       -> (shift_a = 32) // dejar e ir
	  -i ^ asr ^ (shift_a >= 32) ^ (rm is neg)      -> 0xffffffff
	  -i ^ asr ^ (shift_a >= 32) ^ -(rm is neg)     -> 0
	  -i ^ asr ^ -(shift_a >= 32)                    -> static_cast<u32>(static_cast<int32_t>(rm) >> shift_amount)
	  ```


    es un proceso similar al diseño y simplificación máquinas de estado finito.
	
	- en este punto me percato que asr puede simplificarse de sobremanera. ¿porqué? porque podemos aprovecharnos del desplazamiento con preservación de signo también para devolver los valores estáticos y con una regla de comprobación mínimos.
	

  originals (r)

	``` c++
	
    case ASR:
      if (is_special_case)
        shift_amount = 32; // ASR #0
      if (shift_amount >= 32) {

        // Shifting ge 32, a. if and negative -> ffff, b. if and postive -> 0s
        operable_operand2 = (rm & 0x80000000) ? 0xffffffff : 0;
      } else {
        // Preserve sign bit with i32
        operable_operand2 = static_cast<u32>(static_cast<int32_t>(rm) >> shift_amount);
      }
      break;

	```

moderns (tm)


	``` c++	
    case ASR:
      if (is_special_case) {
        shift_amount = 32; // ASR #0
      }

      operable_operand2 = static_cast<u32>(static_cast<int32_t>(rm) >> std::min<u32>(31, shift_amount));
      break;

	```

	por lo que:
	
	``` 
	  (lenguaje lógico)
	  -i ^ lsl ^ special_case                       -> rm
	  -i ^ lsl ^ -special_case ^ (shift_a >= 32)    -> 0
	  -i ^ lsl ^ -special_case ^ -(shift_a >= 32)   -> rm << shift_a
	  -i ^ lsr ^ special_case                       -> (shift_a = 32) // dejar e ir 
	  -i ^ lsr ^ (shift_a >= 32)                    -> 0
	  -i ^ lsr ^ -(shift_a >= 32)                   -> rm >> shift_a
	  -i ^ asr ^ special_case                       -> (shift_a = 32) // dejar e ir
	  -i ^ asr                                      -> static_cast<u32>(static_cast<int32_t>(rm) >> std::min<u32>(31, shift_amount));
	  -i ^ ror ^ special_case                       ->  |= (rm >> 1)
	  -i ^ ror ^ -special_case ^ (shift_a == 0)     -> rm
	  -i ^ ror ^ -special_case ^ -(shift_a == 0)    -> ((rm >> shift_amount) | (rm << (32 - shift_amount)))
    ```


es complicado, pero ayuda podemos decidir más fácilmente cómo optimizar y simplificar.

   - lo cierto es que is_special_case{!four && shift_amount == 0}; y 
    shift_amount = four ? cpu->read_active_register(ISA_ARM_FSR_OPERAND2_RS::get(inst))
                        : ISA_ARM_FSR_OPERAND2_SHIFT_AMOU::get(inst);
    no lo pone nada fácil en codificar.
	
   - sin embargo, pensemos por un momento: el bit 4 es clave !!! y partir de ahí podemos sacar si usar una u otra fórmula de obtención del numérico.
   - en paralelo tenemos shift_type que siempre está en el mismo sitio y en ese sentido no hay tanto problema.
   - el problema tocho viene por el bit 4 que enfunción de este deberemos hacer un doble aplanamiento. Por que intercede si considerar 5 bits o 4 cuatro. Volviéndose peligroso al tener que que crear por cuatro casos de rotación por 2 diferentes implementaciones de extrema semejanza. 
   - esta posiblemente sea una de las grandes desventajas de un código tan corto e hiperespecializado: duplicación de código.
   - sin embargo obtenemos un código con una única responsabilidad. 
   
   
   una idea que se me ocurre de atacar esto es añadiendo una indirección. porque piensa en que tú el fondo lo que te intersa tener para luego en las rotaciones el shift_amount y special_case. 
   AHora pensándolo mejor, la dirección es casi obligatoria. Solo lo es para el caso de cuando el bit 4 esté activo por que recuperará un dato de la cpu. sin embargo aquí la cpu es un ""ente"" ajeno del que es IMPOSIBLE conocer de antemano que devolverá ese read ya que depende de un contexto y estados no relativos a la instrucción. 
   
   Además el tema de bits es lo menos que sea 5 o 4. si solo fuera ese el problema es que sería relativamente sencillo acotar una solución que proporcionase un número. De algún u otro modo, el read nos dificulta el paso al aplanamiento.
   
   como ya hemos dicho en el shift_type hay una serie bien ubicada y sus valores son comprendidos entre límites precisos.

   Pero hemos de percatarnos de un dato de vital transcendencia que no podemos pasar por alto y es que todo special case será con el bit 4 apagado!! Esto quiere decir que el caso especial solo será cuando trabajemos con shift amount es decir cuando bit 4 sea 0 y shift amount sea 0 también.
   
   Desde este nuevo prisma si es posible asumir ciertas simplificaciones.
	
	```   	  
	  (lenguaje lógico)
	   i ^  (rotate == 0)                -> imm
	   i ^ -(rotate == 0)                -> ((imm >> shift_amount) | (imm << (32 - shift_amount)))
	  -i ^ lsl ^ -4 ^  (shift_a == 0)    -> rm
	  -i ^ lsr ^ -4 ^  (shift_a == 0)    -> (shift_a = 32) ^ operand2 = 0 
	  -i ^ asr ^ -4 ^  (shift_a == 0)    -> (shift_a = 32) ^ operand2 = static_cast<u32>(static_cast<int32_t>(rm) >> 31);
	  -i ^ ror ^ -4 ^  (shift_a == 0)    -> comprobar C ^ |= (rm >> 1)
	  -i ^ lsl ^  4 ^  (shift_a >= 32)   -> 0
	  -i ^ lsl ^  4 ^ -(shift_a >= 32)   -> rm << shift_a
	  -i ^ lsr ^  4 ^  (shift_a >= 32)   -> 0
	  -i ^ lsr ^  4 ^ -(shift_a >= 32)   -> rm >> shift_a
	  -i ^ asr ^  4                      -> static_cast<u32>(static_cast<int32_t>(rm) >> std::min<u32>(31, shift_amount));
	  -i ^ ror ^  4 ^  (shift_a == 0)    -> rm
	  -i ^ ror ^  4 ^ -(shift_a == 0)    -> ((rm >> shift_amount) | (rm << (32 - shift_amount)))
    ```

# 10 de julio.

  - nos fijamos en los bits de control y no en los datos. 
  - ojo: si cuando es 0 shift_a y es -4 -> casos especiales. 
  - podemos anticipar el valor de shift_a para casos especiales
  - creo ha llegado de usar el papel.

  - POR PASOS

| Operación                              | I |
|----------------------------------------|---|
| operand2 is immediate value with shift | 1 |
| operand2 is a register with shift      | 0 |

| Operación                                    | I | rotate |
|----------------------------------------------|---|--------|
| imm                                          | 1 | 0      |
| `((imm >> rotate) | (imm << (32 - rotate)))` | 1 | not 0  |
| operand2 is a register with shift            | 0 | x      |

| Operación                                          | I | rotate | bit 4 |
|----------------------------------------------------|---|--------|-------|
| imm                                                | 1 | 0      | x     |
| `((imm >> rotate) | (imm << (32 - rotate)))`       | 1 | not    | x     |
| operand2 is a register with shift (`shift_amount`) | 0 | x      | 0     |
| operand2 is a register with shift (rs)             | 0 | x      | 1     |

| Operación                                          | I | rotate | bit 4 | `shift_amount` |
|----------------------------------------------------|---|--------|-------|----------------|
| imm                                                | 1 | 0      | x     | x              |
| `((imm >> rotate) | (imm << (32 - rotate)))`       | 1 | not    | x     | x              |
| operand2 is a register with shift (`shift_amount`) | 0 | x      | 0     | not 0          |
| operand2 is a register with shift (special case)   | 0 | x      | 0     | 0              |
| operand2 is a register with shift (rs)             | 0 | x      | 1     | x              |

| Operación                                                     | I | rotate | bit 4 | `shift_amount` | `shift_type` |
|---------------------------------------------------------------|---|--------|-------|----------------|--------------|
| imm                                                           | 1 | 0      | x     | x              | x            |
| `((imm >> rotate) | (imm << (32 - rotate)))`                  | 1 | not    | x     | x              | x            |
| operand2 is a register with shift (`shift_amount`)            | 0 | x      | 0     | not 0          | LSL          |
| operand2 is a register with shift (`shift_amount`)            | 0 | x      | 0     | not 0          | LSR          |
| operand2 is a register with shift (`shift_amount`)            | 0 | x      | 0     | not 0          | ASR          |
| operand2 is a register with shift (`shift_amount`)            | 0 | x      | 0     | not 0          | ROR          |
| rm (special case)                                             | 0 | x      | 0     | 0              | LSL          |
| 0 (special case)                                              | 0 | x      | 0     | 0              | LSR          |
| `static_cast<u32>(static_cast<i32>(rm) >> 31)` (special case) | 0 | x      | 0     | 0              | ASR          |
| `(arm7tdmi::C) ? 0x80000000 : 0 | (rm >> 1)`                  | 0 | x      | 0     | 0              | ROR          |
| operand2 is a register with shift (rs)                        | 0 | x      | 1     | x              | LSL          |
| operand2 is a register with shift (rs)                        | 0 | x      | 1     | x              | LSR          |
| operand2 is a register with shift (rs)                        | 0 | x      | 1     | x              | ASR          |
| operand2 is a register with shift (rs)                        | 0 | x      | 1     | x              | ROR          |
	
| Operación                                                                    | I | rotate | bit 4 | `shift_amount` | `shift_type` |
|------------------------------------------------------------------------------|---|--------|-------|----------------|--------------|
| imm                                                                          | 1 | 0      | x     | x              | x            |
| `((imm >> rotate) | (imm << (32 - rotate)))`                                 | 1 | not    | x     | x              | x            |
| operand2 is a register with shift (`shift_amount`)                           | 0 | x      | 0     | not 0          | LSL          |
| operand2 is a register with shift (`shift_amount`)                           | 0 | x      | 0     | not 0          | LSR          |
| operand2 is a register with shift (`shift_amount`)                           | 0 | x      | 0     | not 0          | ASR          |
| operand2 is a register with shift (`shift_amount`)                           | 0 | x      | 0     | not 0          | ROR          |
| rm (special case)                                                            | 0 | x      | 0     | 0              | LSL          |
| 0 (special case)                                                             | 0 | x      | 0     | 0              | LSR          |
| `static_cast<u32>(static_cast<i32>(rm) >> 31)` (special case)                | 0 | x      | 0     | 0              | ASR          |
| `((cpu->read_cpsr() & arm7tdmi::C) << (31 - 29)) | (rm >> 1)` (special case) | 0 | x      | 0     | 0              | ROR          |
| operand2 is a register with shift (rs)                                       | 0 | x      | 1     | x              | LSL          |
| operand2 is a register with shift (rs)                                       | 0 | x      | 1     | x              | LSR          |
| operand2 is a register with shift (rs)                                       | 0 | x      | 1     | x              | ASR          |
| operand2 is a register with shift (rs)                                       | 0 | x      | 1     | x              | ROR          |

	
| Operación                                                                    | I | rotate | bit 4 | `shift_amount` | `shift_type` |
|------------------------------------------------------------------------------|---|--------|-------|----------------|--------------|
| imm                                                                          | 1 | 0      | x     | x              | x            |
| `((imm >> rotate) | (imm << (32 - rotate)))`                                 | 1 | not    | x     | x              | x            |
| operand2 is a register with shift (`shift_amount`)                           | 0 | x      | 0     | not 0          | LSL          |
| operand2 is a register with shift (`shift_amount`)                           | 0 | x      | 0     | not 0          | LSR          |
| operand2 is a register with shift (`shift_amount`)                           | 0 | x      | 0     | not 0          | ASR          |
| operand2 is a register with shift (`shift_amount`)                           | 0 | x      | 0     | not 0          | ROR          |
| rm (special case)                                                            | 0 | x      | 0     | 0              | LSL          |
| 0 (special case)                                                             | 0 | x      | 0     | 0              | LSR          |
| `static_cast<u32>(static_cast<i32>(rm) >> 31)` (special case)                | 0 | x      | 0     | 0              | ASR          |
| `((cpu->read_cpsr() & arm7tdmi::C) << (31 - 29)) | (rm >> 1)` (special case) | 0 | x      | 0     | 0              | ROR          |
| operand2 is a register with shift (rs)                                       | 0 | x      | 1     | x              | LSL          |
| operand2 is a register with shift (rs)                                       | 0 | x      | 1     | x              | LSR          |
| operand2 is a register with shift (rs)                                       | 0 | x      | 1     | x              | ASR          |
| operand2 is a register with shift (rs)                                       | 0 | x      | 1     | x              | ROR          |

aquí estoy observando que el shift_amount del extractor da un u8 que en realidad es un numero de 5 bit (no el registro rs). Por lo tanto sí bit 4 es 0 el número de shift amount jamás podrá ser superior a 31 por su limitación de base binaria y en caso de superarse desbordaría para 32. Así que naturalmente no tiene sentido comprobar que un número es mayor que otro cuando el primero no requiera más bits que el segundo a compararse. Esto induce a que podemos hacer una temprana detección del shiftamoutn por el bit 4 y evitar las comprobaciones de límites con el hallazgo de mínimos y si sera mayor o igual que 32 porque serán ciclos susceptibles a ahorrarse con motivo de la optimización.

| Operación                                                                    | I | rotate | bit 4 | `shift_amount` | `shift_type` |
|------------------------------------------------------------------------------|---|--------|-------|----------------|--------------|
| imm                                                                          | 1 | 0      | x     | x              | x            |
| `((imm >> rotate) | (imm << (32 - rotate)))`                                 | 1 | not 0  | x     | x              | x            |
|------------------------------------------------------------------------------|---|--------|-------|----------------|--------------|
| rm << `shift_amount`                                                         | 0 | x      | 0     | not 0          | LSL          |
| rm >> `shift_amount`                                                         | 0 | x      | 0     | not 0          | LSR          |
| `static_cast<u32>(static_cast<i32>(rm) >> shift_amount)`                     | 0 | x      | 0     | not 0          | ASR          |
| `((rm >> masked_shift) | (rm << (32 - masked_shift)))`                       | 0 | x      | 0     | not 0          | ROR          |
|------------------------------------------------------------------------------|---|--------|-------|----------------|--------------|
| rm (special case)                                                            | 0 | x      | 0     | 0              | LSL          |
| 0 (special case)                                                             | 0 | x      | 0     | 0              | LSR          |
| `static_cast<u32>(static_cast<i32>(rm) >> 31)` (special case)                | 0 | x      | 0     | 0              | ASR          |
| `((cpu->read_cpsr() & arm7tdmi::C) << (31 - 29)) | (rm >> 1)` (special case) | 0 | x      | 0     | 0              | ROR          |
|------------------------------------------------------------------------------|---|--------|-------|----------------|--------------|
| operand2 is a register with shift (rs)                                       | 0 | x      | 1     | x              | LSL          |
| operand2 is a register with shift (rs)                                       | 0 | x      | 1     | x              | LSR          |
| operand2 is a register with shift (rs)                                       | 0 | x      | 1     | x              | ASR          |
| operand2 is a register with shift (rs)                                       | 0 | x      | 1     | x              | ROR          |

Ante este escenario poco podemos averiguar que valor habrá en rs del que posteriormente solo emplean los 8 bits primeros. Esto como ya hemos dicho antes, depende del estado de la cpu que atraviese la cpu por ese momento. Y por tanto poca optimización podemos realizar.

Una vez ya hecho pedazos la función de operand2, lo complicado es ahora determinar los índices que ocuparán las funciones dentro de la lut. Esta tarea no parece ser fácil tampoco. Pero, como todo, hay verlo sobre el papel. Lo cierto es que la lut que tenemos, tendremos una penalización muy grande de espacio y por tanto peor caché y consecuentemente rendimiento bajo. esto es porque tenemos varios valores que no son unos o ceros. Y mayor agravante si consideramos que solo tenemos 14 casos. Los bits necesarios para capturar esos catorce casos son 4. Aquí surge otro reto.

Vayamos por partes. Razonemos un poco sobre lo que hay sobre la mesa: tenemos que el campo rotate se entremezcla con `shift_amount` siendo que ocupen 4 y 5 bits en el mismo espacio, tenemos que el tipo de shift ocupa 2 bits irremediablemente. Luego no hay que confuncir rs con `shift_amount`. El bit i es un buen distintivo.

Lo que podemos hacer es comprimir los valores del normalizador. Los números largos pasan a valer un bit. Esto que que para los únicos casos donde neguemos no hay interferencias con otros valores. Dando lugar a esta tabla

| n  | Operación                                                                    | I | rotate != 0 | bit 4 | `shift_amount` != 0 | `shift_type` |
|----|------------------------------------------------------------------------------|---|-------------|-------|---------------------|--------------|
| 0  | imm                                                                          | 1 | 0           | x     | x                   | x            |
| 1  | `((imm >> rotate) | (imm << (32 - rotate)))`                                 | 1 | 1           | x     | x                   | x            |
|----|------------------------------------------------------------------------------|---|-------------|-------|---------------------|--------------|
| 2  | rm << `shift_amount`                                                         | 0 | x           | 0     | 1                   | LSL          |
| 3  | rm >> `shift_amount`                                                         | 0 | x           | 0     | 1                   | LSR          |
| 4  | `static_cast<u32>(static_cast<i32>(rm) >> shift_amount)`                     | 0 | x           | 0     | 1                   | ASR          |
| 5  | `((rm >> masked_shift) | (rm << (32 - masked_shift)))`                       | 0 | x           | 0     | 1                   | ROR          |
|----|------------------------------------------------------------------------------|---|-------------|-------|---------------------|--------------|
| 6  | rm (special case)                                                            | 0 | x           | 0     | 0                   | LSL          |
| 7  | 0 (special case)                                                             | 0 | x           | 0     | 0                   | LSR          |
| 8  | `static_cast<u32>(static_cast<i32>(rm) >> 31)` (special case)                | 0 | x           | 0     | 0                   | ASR          |
| 9  | `((cpu->read_cpsr() & arm7tdmi::C) << (31 - 29)) | (rm >> 1)` (special case) | 0 | x           | 0     | 0                   | ROR          |
|----|------------------------------------------------------------------------------|---|-------------|-------|---------------------|--------------|
| 10 | operand2 is a register with shift (rs)                                       | 0 | x           | 1     | x                   | LSL          |
| 11 | operand2 is a register with shift (rs)                                       | 0 | x           | 1     | x                   | LSR          |
| 12 | operand2 is a register with shift (rs)                                       | 0 | x           | 1     | x                   | ASR          |
| 13 | operand2 is a register with shift (rs)                                       | 0 | x           | 1     | x                   | ROR          |

En tal caso ahora podemos juntar rotate con bit 4 e interpretar en conjunto con el bit I. Esto lo podemos hacer porque justo para los casos en donde I sea 0 rotate no se considera.


| Operación                                                                    | I | rotate != 0 v bit 4 | `shift_amount` != 0 | `shift_type` |
|------------------------------------------------------------------------------|---|---------------------|---------------------|--------------|
| imm                                                                          | 1 | 0                   | x                   | x            |
| `((imm >> rotate) | (imm << (32 - rotate)))`                                 | 1 | 1                   | x                   | x            |
|------------------------------------------------------------------------------|---|---------------------|---------------------|--------------|
| rm << `shift_amount`                                                         | 0 | 0                   | 1                   | LSL          |
| rm >> `shift_amount`                                                         | 0 | 0                   | 1                   | LSR          |
| `static_cast<u32>(static_cast<i32>(rm) >> shift_amount)`                     | 0 | 0                   | 1                   | ASR          |
| `((rm >> masked_shift) | (rm << (32 - masked_shift)))`                       | 0 | 0                   | 1                   | ROR          |
|------------------------------------------------------------------------------|---|---------------------|---------------------|--------------|
| rm (special case)                                                            | 0 | 0                   | 0                   | LSL          |
| 0 (special case)                                                             | 0 | 0                   | 0                   | LSR          |
| `static_cast<u32>(static_cast<i32>(rm) >> 31)` (special case)                | 0 | 0                   | 0                   | ASR          |
| `((cpu->read_cpsr() & arm7tdmi::C) << (31 - 29)) | (rm >> 1)` (special case) | 0 | 0                   | 0                   | ROR          |
|------------------------------------------------------------------------------|---|---------------------|---------------------|--------------|
| operand2 is a register with shift (rs)                                       | 0 | 1                   | x                   | LSL          |
| operand2 is a register with shift (rs)                                       | 0 | 1                   | x                   | LSR          |
| operand2 is a register with shift (rs)                                       | 0 | 1                   | x                   | ASR          |
| operand2 is a register with shift (rs)                                       | 0 | 1                   | x                   | ROR          |

Pero sin embargo debamos, reconsiderar rehacer la simplificación tomando las expansiones de los símbolos ROR, LSL...

| Operación                                                                    | I | rotate != 0 v bit 4 | `shift_amount` != 0 | `shift_type` |
|------------------------------------------------------------------------------|---|---------------------|---------------------|--------------|
| imm                                                                          | 1 | 0                   | x                   | x            |
| `((imm >> rotate) | (imm << (32 - rotate)))`                                 | 1 | 1                   | x                   | x            |
|------------------------------------------------------------------------------|---|---------------------|---------------------|--------------|
| rm << `shift_amount`                                                         | 0 | 0                   | 1                   | 00           |
| rm >> `shift_amount`                                                         | 0 | 0                   | 1                   | 01           |
| `static_cast<u32>(static_cast<i32>(rm) >> shift_amount)`                     | 0 | 0                   | 1                   | 10           |
| `((rm >> masked_shift) | (rm << (32 - masked_shift)))`                       | 0 | 0                   | 1                   | 11           |
|------------------------------------------------------------------------------|---|---------------------|---------------------|--------------|
| rm (special case)                                                            | 0 | 0                   | 0                   | 00           |
| 0 (special case)                                                             | 0 | 0                   | 0                   | 01           |
| `static_cast<u32>(static_cast<i32>(rm) >> 31)` (special case)                | 0 | 0                   | 0                   | 10           |
| `((cpu->read_cpsr() & arm7tdmi::C) << (31 - 29)) | (rm >> 1)` (special case) | 0 | 0                   | 0                   | 11           |
|------------------------------------------------------------------------------|---|---------------------|---------------------|--------------|
| operand2 is a register with shift (rs)                                       | 0 | 1                   | x                   | 00           |
| operand2 is a register with shift (rs)                                       | 0 | 1                   | x                   | 01           |
| operand2 is a register with shift (rs)                                       | 0 | 1                   | x                   | 10           |
| operand2 is a register with shift (rs)                                       | 0 | 1                   | x                   | 11           |

ESTO ES MUY TOP.

ES MUY IMPORTANTE: PONER N

| n  | Operación                                                                    | I | rotate != 0 | bit 4 | `shift_amount` != 0 | `shift_type` |
|----|------------------------------------------------------------------------------|---|-------------|-------|---------------------|--------------|
| 0  | rm << `shift_amount`                                                         | 0 | x           | 0     | 1                   | LSL          |
| 1  | rm >> `shift_amount`                                                         | 0 | x           | 0     | 1                   | LSR          |
| 2  | `static_cast<u32>(static_cast<i32>(rm) >> shift_amount)`                     | 0 | x           | 0     | 1                   | ASR          |
| 3  | `((rm >> masked_shift) | (rm << (32 - masked_shift)))`                       | 0 | x           | 0     | 1                   | ROR          |
|----|------------------------------------------------------------------------------|---|-------------|-------|---------------------|--------------|
| 4  | rm (special case)                                                            | 0 | x           | 0     | 0                   | LSL          |
| 5  | 0 (special case)                                                             | 0 | x           | 0     | 0                   | LSR          |
| 6  | `static_cast<u32>(static_cast<i32>(rm) >> 31)` (special case)                | 0 | x           | 0     | 0                   | ASR          |
| 7  | `((cpu->read_cpsr() & arm7tdmi::C) << (31 - 29)) | (rm >> 1)` (special case) | 0 | x           | 0     | 0                   | ROR          |
|----|------------------------------------------------------------------------------|---|-------------|-------|---------------------|--------------|
| 8  | imm                                                                          | 1 | 0           | x     | x                   | x            |
| 9  | `((imm >> rotate) | (imm << (32 - rotate)))`                                 | 1 | 1           | x     | x                   | x            |
|----|------------------------------------------------------------------------------|---|-------------|-------|---------------------|--------------|
| 10 | operand2 is a register with shift (rs)                                       | 0 | x           | 1     | x                   | LSL          |
| 11 | operand2 is a register with shift (rs)                                       | 0 | x           | 1     | x                   | LSR          |
| 12 | operand2 is a register with shift (rs)                                       | 0 | x           | 1     | x                   | ASR          |
| 13 | operand2 is a register with shift (rs)                                       | 0 | x           | 1     | x                   | ROR          |

¡SON MAPAS DE Mapas de Karnaugh! (ni me acordaba de FC)

Si organizamos, a conveniencia...
Podemos idenficar que I v bit4 -> 1 para todo n tal que n3 = 1. Es decir, I v b4 -> [8, 16] // 1xxx
Para n2 será 1 si I v (-(r != 0) ^ (s != 0))
Para n1 será -I ^ t1
Para n0 será ((r != 0) ^ I) v (t0 ^ -I)

| n    | Operación                                   | I v b4 | I v (-(r != 0) ^ (s != 0)) | I | r != 0 | b4 | `s` != 0 | `t` |
|------|---------------------------------------------|--------|----------------------------|---|--------|----|----------|-----|
| 0000 | `arm_operand2_compute_i0_40_shifta0_LSL`    | 0      | 0                          | 0 | x      | 0  | 1        | 00  |
| 0001 | `arm_operand2_compute_i0_40_shifta0_LSL`    | 0      | 0                          | 0 | x      | 0  | 1        | 01  |
| 0010 | `arm_operand2_compute_i0_40_shifta0_LSL`    | 0      | 0                          | 0 | x      | 0  | 1        | 10  |
| 0011 | `arm_operand2_compute_i0_40_shifta0_LSL`    | 0      | 0                          | 0 | x      | 0  | 1        | 11  |
|------|---------------------------------------------|--------|----------------------------|---|--------|----|----------|-----|
| 0100 | `arm_operand2_compute_i0_40_shiftanot0_LSL` | 0      | 1                          | 0 | x      | 0  | 0        | 00  |
| 0101 | `arm_operand2_compute_i0_40_shiftanot0_LSR` | 0      | 1                          | 0 | x      | 0  | 0        | 01  |
| 0110 | `arm_operand2_compute_i0_40_shiftanot0_ASR` | 0      | 1                          | 0 | x      | 0  | 0        | 10  |
| 0111 | `arm_operand2_compute_i0_40_shiftanot0_ROR` | 0      | 1                          | 0 | x      | 0  | 0        | 11  |
|------|---------------------------------------------|--------|----------------------------|---|--------|----|----------|-----|
| 1000 | `arm_operand2_compute_i0_41_LSL`            | 1      | 0                          | 0 | x      | 1  | x        | 00  |
| 1001 | `arm_operand2_compute_i0_41_LSR`            | 1      | 0                          | 0 | x      | 1  | x        | 01  |
| 1010 | `arm_operand2_compute_i0_41_ASR`            | 1      | 0                          | 0 | x      | 1  | x        | 10  |
| 1011 | `arm_operand2_compute_i0_41_ROR`            | 1      | 0                          | 0 | x      | 1  | x        | 11  |
|------|---------------------------------------------|--------|----------------------------|---|--------|----|----------|-----|
| 1100 | `arm_operand2_compute_i1_rotate0`           | 1      | 1                          | 1 | 0      | x  | x        | x   |
| 1101 | `arm_operand2_compute_i1_rotatenot0`        | 1      | 1                          | 1 | 1      | x  | x        | x   |

# 17 de julio.

Hoy quiero implementar todas las lógicas.
Pero antes quiero perfeccionar mi and para que actualice los el cpsr flags como toque.
El resto de operaciones creo que será coser y cantar.
Cambiar alguna cosita pero creo que sera fácil.
Lo importante ahora es ver exactamente qué hace la operación y qué implicaciones tiene en los cpsr flags.

es decir vamos a ver cómo se activan V y C en cpsr.
los otros dos son fáciles.

Lo cierto es que viendo la estructura que devuelven las instrucciones creo que hace falta la necesidad de un campo para carry_out. Aunque entiendo de mi yo del pasado para devolver el shift amount, lo cierto es que puede no tener las mismas implicaciones para todos los casos y resulta absurdo tener una lut y luego en concretar un qué hacer hiperespecializado... Pasando por comprobaciones muy similares y añadiendo mayor carga de overhead.

Estoy comprobando que la mantenibilidad es muy baja. Por todas las cosas que hay que cambiar.
Este proyecto https://github.com/nba-emu/NanoBoyAdvance/blob/master/src/nba/src/arm/handlers/handler32.inl una vez más demuestra lo fácilmente descriptivo que es c++ con las plantillas. 

``` c++
  int carry = state.cpsr.f.c;
  u32 op1;
  u32 op2;

  pipe.access = Access::Code | Access::Sequential;

  if constexpr (immediate) {
    int value = instruction & 0xFF;
    int shift = ((instruction >> 8) & 0xF) * 2;

    if (shift != 0) {
      carry = (value >> (shift - 1)) & 1;
      op2   = (value >> shift) | (value << (32 - shift));
    } else {
      op2 = value;
    }

    op1 = GetReg(reg_op1);
  } else {
    u32 shift;

    if constexpr (shift_imm) {
      shift = (instruction >> 7) & 0x1F;
    } else {
      shift = GetReg((instruction >> 8) & 0xF);
      state.r15 += 4;
      bus.Idle();

      pipe.access = Access::Code | Access::Nonsequential;
       }

    op1 = GetReg(reg_op1);
    op2 = GetReg(reg_op2);

    DoShift(shift_type, op2, shift, carry, shift_imm);
  }
```


claro, con este código de así concentramos todo en uno.

``` c++
template <bool a> int get_operand2(int b) { return a ? 1 : b; }
auto v = get_operand2<true>; // es un int(*)(int)
auto b = v(2);               // es un int
```

vale, pensaba era más simple pero no. Hay faena por hacer. Creo que hacerlo de esta forma centralizará y formentará la mantenibilidad. Reducirneod incosistencias y duplicidad de código.

Vale en esta nueva versión he tomado en cuenta el carry y todos los edge cases. Esto posiblemente dé para otra lut y utilizar karnaugh para simplificar saltos ifs, pero de momento hay que tener algo funcando, pero me ha jodido el carry. Creo que es una idea muy certera que pueda llevarse a cabo para optimizar y volver a las luts con karnaugh.

De momento vamos tirando así. Cons ifs. 

He "estilizado" el código para hacer más idiomático.

Yo creo que esto lo dejamos aparcado para seguir con las instrucciones.


The condition codes in the CPSR may be preserved or updated as a result of this instruction,
according to the value of the S bit in the instruction.

Certain operations (TST, TEQ, CMP, CMN) do not write the result to Rd. They are used only to
perform tests and to set the condition codes on the result and always have the S bit set.

The logical operations (AND, EOR, TST, TEQ, ORR, MOV, BIC, MVN) perform the logical action on all
corresponding bits of the operand or operands to produce the result. If the S bit is set (and Rd
is not R15, see below) the V flag in the CPSR will be unaffected, the C flag will be set to the
carry out from the barrel shifter (or preserved when the shift operation is LSL #0), the Z flag
will be set if and only if the result is all zeros, and the N flag will be set to the logical
value of bit 31 of the result.

logical -> -update(V)
(S ^ -r15) > -update
-S v r15 > update
	
<<< aquí veo un potencial comportamiento común. Las lógicas no tocan V ni aunque lo tengan S. Podemos de alguna forma estandarizar este comportamiento para toda lógica que se meta.
	
The arithmetic operations (SUB, RSB, ADD, ADC, SBC, RSC, CMP, CMN) treat each
operand as a 32 bit integer (either unsigned or 2’s complement signed, the two are
equivalent). If the S bit is set (and Rd is not R15) the V flag in the CPSR will be set if
an overflow occurs into bit 31 of the result; this may be ignored if the operands were
considered unsigned, but warns of a possible error if the operands were 2’s


 complement signed. The C flag will be set to the carry out of bit 31 of the ALU, the Z
flag will be set if and only if the result was zero, and the N flag will be set to the value
of bit 31 of the result (indicating a negative result if the operands are considered to be
2’s complement signed).

<<< no obstante hay cosas que comparten en común. como el hecho de proceder a actualizar las banderas. ¿Estás pensando en plantillas? yo también.

If R15 (the PC) is used as an operand in a data processing instruction the register is
used directly.
The PC value will be the address of the instruction, plus 8 or 12 bytes due to instruction
prefetching. If the shift amount is specified in the instruction, the PC will be 8 bytes
ahead. If a register is used to specify the shift amount the PC will be 12 bytes ahead.

<<< esto es importante: PC cambia. 

If R15 (the PC) is used as an operand in a data processing instruction the register is
used directly.
The PC value will be the address of the instruction, plus 8 or 12 bytes due to instruction
prefetching. If the shift amount is specified in the instruction, the PC will be 8 bytes
ahead. If a register is used to specify the shift amount the PC will be 12 bytes ahead.



4.5.6 TEQ, TST, CMP and CMN opcodes
Note
TEQ, TST, CMP and CMN do not write the result of their operation but do set flags in
the CPSR. An assembler should always set the S flag for these instructions even if this
is not specified in the mnemonic.
The TEQP form of the TEQ instruction used in earlier ARM processors must not be
used: the PSR transfer operations should be used instead.
The action of TEQP in the ARM7TDMI-S is to move SPSR_mode to the CPSR if the
processor is in a privileged mode and to do nothing if in User mode.

<<< lo lógico vaya.

de momento voy a montar una estructura de plantillas que sirva para definir qué instrucción es cada cosa y minimizar duplicidades y errores en común. Luego a partir de ahí vamos perfeccionando.
Mi planteamiento inicial es crear una común que acepte un lambda donde haga de por sí la operación solicitada y otro lambda para la actualización de bits. 
SIn embargo, creo que el lambda es lo más bobo... bueno no, en la común creo que sí tiene sentido... No mejor no, no deleguemos más trabajo al compilador. Vamos a evitarle a toda costa la posible indirección del salto.
Entonces la común tendrá un funcionamiento talque primero coja todos los operandos, llame para obtener operand2, operación en cuestión definida por el lambda y luego un if constexpr (caso) para qué actualizar o no actualizar.
Esto último nos puede dar flexibilidad para decidir qué considerar en la futura lut que aglutine todas las operaciones y podamos saltar directamente a ejecutar al sitio que interese con los efectos colaterales que nos interese.

# 18 de julio

He llegado a la conclusión de que es mejor definir un conjunto finito en lugar de dar indirección. De modo que la prioridad para optimizar código con lut sea:

1. Es un conjunto de valores muy concretos? Entonces plantilla y en tiempo de compilación handlear todo eso. Abstraiga los valores concretos a tiempo de compilación
- Vale para cualquier cosa: tipo receta (todo es igual pero cambia una parte solo, lambdas) 

2. Es una función que puede ser utilizada a convenienza múltiples veces? lambda.
- lo recomendable es que el compilador sea capaz de hacerle el inline si es una función simplona.

3. es un valor demasiado grande? quizás podría ser karnaugh pero es mejor simplicarlo lógicamente, como por ejemplo trabajar algo_grande != 0. O dividirlo en varias variables que ayuden a identificar. En otro caso pasar al siguiente.

4. es un valor demasiado grande y hay indirección para conocerlo? Esto es que hay un valor que solo se conoce en tiempo de ejecución y compilación. Por lo tanto aquí no podemos optimizar nada. Toca pasar por el aro y aguardar para que el compilador haga su faena muy bien.

5. Si después de todo puedes ver que hay patrón que se repite, quizás sea indicativo para revisar y abstraer más variables. Pero esto es solo recomendable en fases muy estables y consolidades o con una batería de prueba demasiado exhaustiva.

Entonces creo que tomar en cuenta que hay una plantilla común no es lo más adecuado. Sí bien es cierto que hay código que estará en ambas, lo cierto es que es muy minúsculo y no prohibitivo. No derivaremos y haremos clases de funciones concretas.

Además de que si lo pensamos bien, el conjunto de operaciones no es tanto. `arm_fsr_opcode` solo tiene 16 valores posibles. Y no creo que vaya necesariamente poner un lambda. Precisamente ya el mero echo de que tengamos bien definido este enum `arm_fsr_opcode` es un indicativo que es finito. Un lambda puede llegar agregar indirección. pero esa decisión la delegamos al compilador si hacer inline o no. Propongo que la plantilla en tiempos de compilación evalúe el trozo que le interese poner en hueco de la operación.

Esto tiene otra ventaja y es que podemos despreocuparnos de la ventana de contexto del lambda. Ampliándola a toda la plantilla y sin "paso de parámetros" con referencia ni punteros. Lo cierto que es que no tenemos que definir qué parámetros irán en el lmanda y omitimos el rollazo de cambiarlo de posición porque lol no he considerado un edge case entre las 16 opciones.

Otra cuestión que voy aprovechar es refactorizar `enum` para hacer servir `enum class`. Esto se debe principalmente a aplicar buenas prácticas de programación del lenguaje y hacer lo más idiomático.

hecho. 

Se me ocurre mejor juntarlo todo en uno y decir en tiempo de compilación su es uno u otro (lógico o aritmético).

Esto es una barbaridad de rápido. Y todo muy práctico a hacer refactors ad hoc al vuelo. => esto es que me pongo a implementar los primeros y de repente veo que hay un caso especial que ignora o lo que sea, y es muy directo a modificar una parte solo.

He decidido en añadir variables para conocer los shift de los bits de interés del cpsr.


Ya tengo esto, algo básico con lo que poder trabajar cómodamente e ir aplicando mejoras conforme vea.
Ahora voy a ver la especificación y ver que pasa.

``` c++

template <bool s, arm_fsr_opcode opcode> void arm_fsr_generator(arm7tdmi& cpu, u32 inst) {
  // Meta template variables
  constexpr auto is_logical{opcode == arm_fsr_opcode::AND || opcode == arm_fsr_opcode::EOR ||
                            opcode == arm_fsr_opcode::TST || opcode == arm_fsr_opcode::TEQ ||
                            opcode == arm_fsr_opcode::ORR || opcode == arm_fsr_opcode::MOV ||
                            opcode == arm_fsr_opcode::BIC || opcode == arm_fsr_opcode::MVN};
  constexpr auto can_write_rd{!(opcode == arm_fsr_opcode::TST || opcode == arm_fsr_opcode::TEQ ||
                                opcode == arm_fsr_opcode::CMP || opcode == arm_fsr_opcode::CMN)};

  // Retrieve values
  auto rn_idx{ISA_ARM_FSR_RN::get(inst)};
  auto rd_idx{ISA_ARM_FSR_RD::get(inst)};

  u32 c_in = (cpu.read_cpsr() & arm7tdmi::C) ? 1 : 0;
  u32 op1;
  if constexpr (opcode != arm_fsr_opcode::MOV && opcode != arm_fsr_opcode::MVN)
    op1 = cpu.read_active_register(rn_idx);

  auto op2{arm_operand2_lut.run(inst, cpu, inst)};
  u32 res{};

  // Perform operation
  if constexpr (opcode == arm_fsr_opcode::AND || opcode == arm_fsr_opcode::TST) {
    res = op1 & op2.result;
  } else if constexpr (opcode == arm_fsr_opcode::EOR || opcode == arm_fsr_opcode::TEQ) {
    res = op1 ^ op2.result;
  } else if constexpr (opcode == arm_fsr_opcode::SUB || opcode == arm_fsr_opcode::CMP) {
    res = op1 - op2.result;
  } else if constexpr (opcode == arm_fsr_opcode::RSB) {
    res = op2.result - op1;
  } else if constexpr (opcode == arm_fsr_opcode::ADD || opcode == arm_fsr_opcode::CMN) {
    res = op1 + op2.result;
  } else if constexpr (opcode == arm_fsr_opcode::ADC) {
    res = op1 + op2.result + c_in;
  } else if constexpr (opcode == arm_fsr_opcode::SBC) {
    res = op1 - op2.result + c_in - 1;
  } else if constexpr (opcode == arm_fsr_opcode::RSC) {
    res = op2.result - op1 + c_in - 1;
  } else if constexpr (opcode == arm_fsr_opcode::ORR) {
    res = op1 | op2.result;
  } else if constexpr (opcode == arm_fsr_opcode::MOV) {
    res = op2.result;
  } else if constexpr (opcode == arm_fsr_opcode::BIC) {
    res = op1 & ~op2.result;
  } else if constexpr (opcode == arm_fsr_opcode::MVN) {
    res = ~op2.result;
  }

  // write back the result
  if constexpr (can_write_rd) {
    cpu.write_active_register(rd_idx, res);
  }

  // Side effects
  if constexpr (s) {
    auto z{res == 0 ? arm7tdmi::Z : 0};
    auto n{(res & 0x80000000) != 0 ? arm7tdmi::N : 0};
    auto v{rd_idx == pc ? 0 /* update logic */ : cpu.read_cpsr() & arm7tdmi::V};

    cpu.set_cpsr(arm7tdmi::Z | arm7tdmi::N | arm7tdmi::C | arm7tdmi::V, z | n | v);
  }
}

```

Esto nos dice la especificación.

The logical operations (AND, EOR, TST, TEQ, ORR, MOV, BIC, MVN) perform the logical action on all
corresponding bits of the operand or operands to produce the result. If the S bit is set (and Rd
is not R15, see below) the V flag in the CPSR will be unaffected, the C flag will be set to the
carry out from the barrel shifter (or preserved when the shift operation is LSL #0), the Z flag
will be set if and only if the result is all zeros, and the N flag will be set to the logical
value of bit 31 of the result.

<<<
Aquí destacamos que:

- las lógicas tienen un tratamiento especial.
- Siendo S := bit s activo, R := rd es 15, F := actualiza banderas
  - S ^ -R -> F
  
- V = default
- C = shift Barrel
- N = 80...
- Z = 00...

<<<

The arithmetic operations (SUB, RSB, ADD, ADC, SBC, RSC, CMP, CMN) treat each
operand as a 32 bit integer (either unsigned or 2’s complement signed, the two are
equivalent). If the S bit is set (and Rd is not R15) the V flag in the CPSR will be set if
an overflow occurs into bit 31 of the result; this may be ignored if the operands were
considered unsigned, but warns of a possible error if the operands were 2’s complement signed. 
The C flag will be set to the carry out of bit 31 of the ALU, the Z flag will be set if and 
only if the result was zero, and the N flag will be set to the value of bit 31 of the result 
(indicating a negative result if the operands are considered to be 2’s complement signed).

<<<
Aquí destacamos que:

- las arithmetics tienen un tratamiento especial.
- ojo con signo y sin signo.
- S ^ -R -> F
  
- V = over 31
- C = cout Alu
- N = 80...
- Z = 00...
<<<

Bien, con esta info que podríamos considerar efectuar los siguientes cambios. Vemos claramente que la relación con la variable lógica que definimos antes R tiene mucho que ver. Rd es un campo de locación fija dentro del campo de instrucción. Esto es que no se mueve y por ende estará en la misma posición siempre. El valor de r15 se codifica como 1111 por lo que podemos identificar fácilmente con un operador and dado que solo nos importa el índice y no el contenido de r15.

con el simulador jarmemu, https://cpulator.01xz.net/?sys=arm (más preciso)

``` assembly
.global _start
.text
_start:
  @ Beginning of the program
  mov r2, #16
  mov r5, #0x80000000
  mov r6, #1
  mov r2, #4
  ands pc, r5, r2 % es legal que s esté habilitado?
  mov r2, #2
  mov r2, #2
  mov r2, #2
  mov r2, #2
  mov r2, #2
  ands r2, r5, r2
```

ejercicio 1

`and pc, r5, r2` = `0xe005f002` = `1110 0000 0000 0101 1111 0000 0000 0010`

| 1110      | 00  | 0 | 0000   | 0 | 0101 | 1111 | 0000 0000 0010 |
|-----------|-----|---|--------|---|------|------|----------------|
| condición | lol | I | opcode | S | r5   | pc   | r2             |

 ----????....====!!!!AAAAçççç
`11100000000001011111000000000010`

ejercicio 2

`ands pc, r5, r2` = `0xe015f002` = `1110 0000 0001 0101 1111 0000 0000 0010`

| 1110      | 00  | 0 | 0000   | 1 | 0101 | 1111 | 0000 0000 0010 |
|-----------|-----|---|--------|---|------|------|----------------|
| condición | lol | I | opcode | S | r5   | pc   | r2             |

 ----????....====!!!!AAAAçççç
`11100000000101011111000000000010`


Vale, otro comportamiento que podemos optimizar es delegar la recuperación del valor de c_in a la función de cómputo de operand2.
¿Por qué?
Bueno en realidad, en la base del código actual hacemos esta recuperación dos veces cuando no es necesario.
Una operación de procesamiento de datos efectúa esta recuperación 

``` c++
u32 c_in = (cpu.read_cpsr() & arm7tdmi::C) >> arm7tdmi::C_SHIFT;
```

pero dentro de la lut de operands2 llevamos a cabo otra recuperación.

``` c++
template <bool i, bool rotate_zero = false, bool bit4 = false, bool shift_zero = 0,
          arm_shift_type shift_type = arm_shift_type::LSL>
arm_operand2_result arm_operand2_generator(arm7tdmi& cpu, u32 inst) {
  auto carry_out{static_cast<u8>(cpu.is_cpsr(arm7tdmi::C, arm7tdmi::C))};
```

sabiendo que operand2 es un paso obligatorio para toda operación de ALU, podemos evitar duplicidades y recuperar del generador direcamente.
Es una tontería así de grande pero cada cosa importa.


<<<
- las lógicas tienen un tratamiento especial.
- V = default
- C = shift Barrel
- N = 80...
- Z = 00...
<<<

<<<
- las arithmetics tienen un tratamiento especial.
- V = over 31
- C = cout Alu
- N = 80...
- Z = 00...
<<<


Podemos aprovechar que expandir el resultado a 64 bits en lugar de 32 para y así detectar más fácil el efecto overflow.

Vale.

Bueno ya ha es otro día.

# 19 de julio.

España juega la mundial contra la Argentina. ¡Qué gane España!
Se palpa un ambiente de poca división que recientemente no se ve.
Aunque no se muy futbolero, considero que esto es muy positivo.
Y más si vemos el contexto de crispación, escándalos y desastres en los últimos tiempos.
A ver si sale la segunda estrella...

Estoy mirando en optimizar el código de generación de instrucciones. He implementado siguiendo la instruccón que recupere el spsr al cpsr si el destino es 15 según como se indica en la documentación:

``` c++
if constexpr (rd_pc) 
	cpu.write_cpsr(cpu.read_spsr());


```

"When Rd is a register other than R15, the condition code flags in the CPSR may be
updated from the ALU flags as described above.
When Rd is R15 and the S flag in the instruction is not set the result of the operation is
placed in R15 and the CPSR is unaffected.
When Rd is R15 and the S flag is set the result of the operation is placed in R15 and
the SPSR corresponding to the current mode is moved to the CPSR. This allows state
changes which atomically restore both PC and CPSR. This form of instruction should
not be used in User mode."

He implementado los efectos colaterales para grabar en cpsr diferenciando si sea lógica o no sencillamente. 
En las aritméticas, hay un error en considerar en cual sea el primer operando porque se reviertes para algunas operaciones.
Por lo mi propuesta inicial fue hacer un intercambio de variables para ese caso. Sin embargo, ví la oportunidad de reducir el código del if de operaciones, si realizacemos el intercambio antes de efectuar la operación y después de obtener los operandos 1 y 2. Mi planteamineto inicial fue 

``` c++

  if constexpr (is_inverted_sub) { // a^b^b = a <-> https://youtube.com/watch?v=4KdvcQKNfbQ
    op1 ^= op2.result;
    op2.result ^= op1;
    op1 ^= op2.result;
  }

  // Perform operation
  if constexpr (opcode == arm_fsr_opcode::AND || opcode == arm_fsr_opcode::TST)
    res = op1 & op2.result;
  else if constexpr (opcode == arm_fsr_opcode::EOR || opcode == arm_fsr_opcode::TEQ)
    res = op1 ^ op2.result;
  else if constexpr (opcode == arm_fsr_opcode::SUB || opcode == arm_fsr_opcode::CMP ||
                     opcode == arm_fsr_opcode::RSB)
    res = static_cast<u64>(op1) - op2.result;
  else if constexpr (opcode == arm_fsr_opcode::ADD || opcode == arm_fsr_opcode::CMN)
    res = static_cast<u64>(op1) + op2.result;
  else if constexpr (opcode == arm_fsr_opcode::ADC)
    res = static_cast<u64>(op1) + op2.result + op2.carry_in;
  else if constexpr (opcode == arm_fsr_opcode::SBC || opcode == arm_fsr_opcode::RSC)
    res = static_cast<u64>(op1) - op2.result + op2.carry_in - 1;
  else if constexpr (opcode == arm_fsr_opcode::ORR)
    res = op1 | op2.result;
  else if constexpr (opcode == arm_fsr_opcode::MOV)
    res = op2.result;
  else if constexpr (opcode == arm_fsr_opcode::BIC)
    res = op1 & ~op2.result;
  else if constexpr (opcode == arm_fsr_opcode::MVN)
    res = ~op2.result;

```

aplicando la propiedad xor de memoria que recordé de un vídeo en el que no se podía utilizar una variable auxiliar. Sin embargo, esto queda en una curiosidad más en que en una funcionalidad, existe la función std::swap que en teoría es mejor porque delega la tarea al compilador el método a elegir para dar el cambiazo de dos variables de formas fáciles. Si vemos el código, es casi un hack porque es literalmente cambiar lo que toca op1 y op2.result para evitar cambios mayores. Al margen de la propiedad, he aplicado el std::swap para más idiomatez.

Al margen de esto, esto ha permitido agrupar algo más el bloque de perform operation siendo que ahora no hay accciones que hagan lo mismo escritas por mi a mano.

Ya desde aquí estaba servido el manejo de bits llegando a optar por evitar desplazar innecesariamente o hacer suposiciones o hacer los cálculos parciales para completarlos para que puedan ser alterados a conveniencia. Este último caso es sobre todo para el efecto colateral de las aritméticas cuando s y por si la operación efectuada no es una suma que invierta las variables c y v computados parcialmente y luego aplicar lo mismo para cualquier caso de aritmética.

``` c++
        // another meta template info
        constexpr auto is_sum{opcode == arm_fsr_opcode::ADD || opcode == arm_fsr_opcode::ADC ||
                              opcode == arm_fsr_opcode::CMN};

        // (res >> 32) & 1 es 1 o 0.
        auto c{static_cast<u32>(res >> 32)};
        auto v{~(op1 ^ op2.result)};

        if constexpr (not is_sum) {
          c = !c;
          v = ~v;
        }

        // Mover lo necesario!
        c = (c & 1) << arm7tdmi::C_SHIFT;
        // movemos lo justo el bit 31 resultante a la posición de V.
        v = (v & (op1 ^ res32) & 0x80000000) >> (31 - arm7tdmi::V_SHIFT);

        cpu.set_cpsr(arm7tdmi::Z | arm7tdmi::N | arm7tdmi::C | arm7tdmi::V, z | n | c | v);
```

He documentado esa función con tal de aumentar la mantenibilidad. Y he añadido algunos comentarios para ver soy consciente de lo que he hecho.

Pero no sé después de ponerme una extensión de documentación mi emacs va lento... Ya veré como solvento esto o igual es cosa del lenguaje o del clangd.

Vale lo he quitado y he optado por hacerlo a mano. Tampoco es que haya muchas opciones si buscamos más funcionalidades.
He pensado que para la memoria y para el tamaño de alcance de proyecto he pensado en utilizar doxygen. Una plataforma que genera documentación del código resultando en una web navegable.

Creo que es algo muy buena práctica.

He cambiado algunos métodos de la lut con tal de hacerlo más al al estilo de stl containers. Como data e invoke.
He refactorizado lut para que no definamos el tipo de retorno porque es algo nicho. Y en su defecto, he utilizado una característica del lenguaje para autodeterminar del tipo de retorno en base a lo que se almacena en la lut si sea llamable habilitará un método que invocación, en otro caso no: dando error de compilación.

Es decir que ahora si almacenamos un int (algo que no es invocable), no dejará realizar el invoke. Si almacenamos funciones sí deja.
Además, ahora sí compila con g++ y clang sin problemas y bajado las versiones porque estoy en debian "versiones estables".
El error es que g++ es más riguroso que clang++, siendo que no permite utilizar using de clases base en derivadas en tiempo de compilación por considerarse incompletas. Pero no ocurre para los tipos concretos. Los using sirven como alias de tipos.

Mis siguientes pasos son:
1. Hacer testing de operand2 y de operaciones de arm fsr. (hoy)
2. Luego si esto va, crear una lut iniciar parcial para saber como direccionar estas operaciones. (hoy-mañana)
3. Probarla. (mañana)
4. Diseñar un esquema básico de memoria con chip. (mañana + 4 días)
5. Preparar estado del arte
6. Preparar preguntas y reunión.

# 21 de julio

con motivo de las celebraciones, el plan no sé cumplió para nada lol.

Por tanto vamos a hacer hoy:

1. Hacer testing de operand2 y de operaciones de arm fsr.
2. Luego si esto va, crear una lut iniciar parcial para saber como direccionar estas operaciones. 
3. Probarla.
4. Diseñar un esquema básico de memoria con chip. (mañana + 4 días) (Vamos a intentarlo, o dejarlo planteado)

Bien, para probar nuestras cosas debemos seguir un orden y por ello cabe recordar las dependencias que tendremos en un futuro.

```

instrucción en crudo y cpu -> [lut de instrucciones] -> [operación fsr] -> [lut de operand2] -> [operand2]

```

La idea de probar es que vamos a probar las dependencias que dependan menos primero. De forma que así aislaremos los fallos por niveles. Siendo que primero, probaremos operand2 y luego fsr. 

Vamos a aprovechar el la estrategia de mocking para probar operand2 directamente desde su llamada de lut. De esta forma mataremos dos pájaros de un tiro, probaremos internamente cómo funciona operand2 y si la lut redirecciona a la que debe. Aunque para un tester más purista lo haría por separado, lo cierto es que aquí podemos considerar la implementación de operand2 y lut de operand2 como completa y es poco susceptible a cambios. Además que su forma principal de interacción es a través de la lut.

Vamos a utilizar una fixture que construya la cpu y el estado del mockeo. El claro beneficio que tiene utilizar una megaplantilla es el rendimiento y que no hay una combinación explosiva de funciones a probar sino que podemos considerarlo todo como un algoritmo y por tanto resulta más fácil ver el transcurso del programa

Vamos a empezar en orden y vamos a ir comprobando las bifurcaciones.

Vale no, vamos a hacer primero pruebas unitarias y luego sobre la lut con mockeos. Aunque en realidad no hace falta para nada. La lut es un array del podemos recuperar el puntero función y ver si lo recuperado coincide. Siendo así que podemos garantizar su correcta ejecución. Podemos establecer un test parametrizado.

Para probar `arm_fsr_operand2_i1_r1` necesitamos solo un caso dado que no tiene bifurcación alguna.
Para probar `arm_fsr_operand2_i1_r0` necesitamos solo un caso dado que no tiene bifurcación alguna pero vamos a comprobar si realmente va bien el carry_out del shift barrel. Por lo que haremos 2.

Ya hemos terminado con i=1, ahora vamos i=0:

Vamos a empezar con los casos especiales y luego seguimos con resto. Los casos especiales siempre tendrán el bit 4 a uno. Y presisaremos de 3 casos más otros 4 para comprobar la activación del carryout, con excepción del lsl.


Vale he encontrado un bug en la cpu y es que no accede bien a los registros `active_registers` por medio del depurador. Vale mala mía, me he olvidado de poner el usr mode mano porque este también cambia los registros. y claro todos los del active son cero porque apuntan al primer elemento. y ningún otro es alterado.

Por otro lado estoy pensando que podríamos seguir matando dos pájaros de un tiro. Y es comprobar que la operación de computar el contenido de operand2 ha ido bien e inmediatamente después ver si en la lut coincide el puntero.

He notado otro fallo en la normalización de índice para la lut de operand2. Los bits de n1 n2 del shift type están dados la vuelta. (lol). Y luego que la máscara máxima de la lut era mal computada si el número no esta uno desplazado n. Este último problema no hubiera surgido si no hubiéramos optado por & en lugar %. 

$$2 \mathbin{\&} 13 \implies \mathtt{0b0010} \mathbin{\&} \mathtt{0b1101} = \mathtt{0b0000} \implies 0$$

En realidad el problema no era el acceso al std::array, pues maneja la manipulación de índices de fuera de sus alcances, pero en la nuestra implementación de la lut preferimos optar por desplazaminetos y máscaras para mayor velocidad. Sin embargo vamos a parchear esto precomputando una máscara con un algoritmo algo más enrevesado para computar la máscara máxima. En realidad no hace falta la máscara pero nos da una mínima garantía.

Para solventar vamos a implementar un algoritmo que ejecute al inicio para computar esto. 

``` c++
inline constexpr std::size_t compute_max_mask(std::size_t n) {
  static_assert(max_length > 1, "You should not use LUT to store less than 2 elements!");
  // static_assert(max_length < sizeof(std::size_t), "Too many items");

  std::size_t mask{0x0};
  auto is_not_powered_2{false};

  for (std::size_t i{0}; i < sizeof(std::size_t); ++i) {
    n <<= 1;
    auto is_one_bit{n & 0x1};
    auto is_more_than_one{(n << 1) != 0};

    if (is_more_than_one || is_not_powered_2) {
      mask |= 1 << i;
      if (is_one_bit) {
        is_not_powered_2 = true;
      }
      continue;
    }

    if (is_one_bit)
      break;
  }

  return mask;
};

```

Pero sin embargo ya una fórmula idomática de hacerlo y es usando `std::bit_ceil(max_length) - 1`.

La idea es aquí de dada la longitud máxima de una lut, sacar la máscara de seguida unos que cubra todos los casos. Es perfecto para 1<<algo pero conplejo para números que no cumplan con la restricción. Esta forma idomática nos ahorra crear una prueba unitaria adicional por lo que siempre que podemos reciclar piezas de otras personas mejor, porque menos tocará revisar. Esta es una de las buenas prácticas de programación y del Software en general. Además este incidente ha servido para remarcar la importancia de las pruebas, porque son lo que realmente nos moldea a arreglar decisiones de errores poco evidentes o imperceptibles.

Volviendo a las pruebas, voy a rellenar las de operand2 con sus comprobaciones para el acceso por la lut y garantizar así la disponibilidad del código.
Además esto demuestra una vez más que el echo comparar funciones es posibles puesto que son punteros simplemente y no realizan copias raras e interminables del código y asignando nuevos códigos. Esto es lo que yo me temía que ocurrise por toda la tontería de copias, movimiento y operadores invisibles de c++, pero no ha sido así.

De hecho, el cambio que hemos hecho en la creación de la tabla de operand2 que consiste en extraer del lambda la creación de funciones adhoc ha tenido cero impacto en espacio, puesto que la tabla tenía que estar compuesta de punteros sí o sí, y su extracción facilita las pruebas. 

``` c++
table.put_raw(0b0100, arm_fsr_operand2_i0_40_z0_LSL);
```

creo que me estoy volviendo un poco loco con crear toda una explosión explosiva de combinaciones de casos. Lo mejor en este caso es crear test parametrizados. Hay una alta repetición del mismo código que puñetero asco leer lo mismo y perderse. Por lo que considero que la mejor baza es crear como test plantilla.

Google Test proporciona un mecanismo de hacer test parametrizados fácilmente. De esta forma no dependemos de una sintaxis sino de poner bien los valores.

Además me gustaría aprovechar para añadir una nueva funcionalidad a los extractores del isa. Y es que veo esto un problema cuando creamos instrucciones. Lo cierto es que la creación actual es muy hacerlo recursivo y no podemos concatenarlo. Bueno sí que podemos. Pero se hace recursivo e igual puede a ver cierta dificultad a la hora de entender que instrucción se construye.

``` c++
// Ahora
u32 inst = ISA_ARM_FSR_I::set1(ISA_ARM_FSR_OPERAND2_IMM::set(ISA_ARM_FSR_OPERAND2_ROTATE::set(templates, 2), 1));

// Propuesta
u32 inst = templates | ISA_ARM_FSR_I::set1() | ISA_ARM_FSR_OPERAND2_IMM::set(1) | ISA_ARM_FSR_OPERAND2_ROTATE::set(2);
```

Aunque esto sea mucho más claro de leer lo cierto sería muy complicado poner bits a cero. Pero para simplificar las cosas vamos a suponer ceros y por este método no interesa la limpieza. Para ejemplificarlo aún más todos estos nuevos métodos serán set_high() para demostrar que solo pone 1 y no borra nada.

Hecho.

Entonces ya una vez visto como hacer tests parametrizados definamos los casos nuevamente porque de tanto hacer he perdido el hilo y creo que es necesario tener esto para hoy.

siendo op2<...>= `template <bool i, bool rotate_zero, bool bit4, bool special_zero_shift, arm_shift_type shift_type>`

0. op2<1, 1>, c = any -> imm y c = any.

1. op2<1, 0>, c = 0 -> imm rot y c = 0.
2. op2<1, 0>, c = 1 -> imm rot y c = 1.

3. op2<0, x, 0, 1, lsl>, c = any -> rm y c = any.

4. op2<0, x, 0, 1, lsr>, c = 1 -> 0 y c = 1.
5. op2<0, x, 0, 1, lsr>, c = 0 -> 0 y c = 0.

6. op2<0, x, 0, 1, asr>, c = 0 -> asr #0 rm y c = 0.
7. op2<0, x, 0, 1, asr>, c = 1 -> asr #0 rm y c = 1.

8. op2<0, x, 0, 1, ror>, c = 0 -> ror #0 rm y c = 0.
9. op2<0, x, 0, 1, ror>, c = 1 -> ror #0 rm y c = 1.

10. op2<0, x, 1, x, lsl>, c = any, rs = 0 -> rm y c = any.
11. op2<0, x, 1, x, lsl>, c = 1, rs < 32 -> rm shifted rs y c = 1.
12. op2<0, x, 1, x, lsl>, c = 0, rs < 32 -> rm shifted rs y c = 0.
13. op2<0, x, 1, x, lsl>, c = 1, rs = 32 -> 0 y c = 1.
14. op2<0, x, 1, x, lsl>, c = 0, rs = 32 -> 0 y c = 0.
15. op2<0, x, 1, x, lsl>, c = any, rs > 32 -> 0 y c = 0.

16. op2<0, x, 0, 0, lsl>, c = 0, shiftamount < 32 -> rm shifted shiftamount y c = 0.
17. op2<0, x, 0, 0, lsl>, c = 1, shiftamount < 32 -> rm shifted shiftamount y c = 1.

18. op2<0, x, 1, x, lsr>, c = any, rs = 0 -> rm y c = any.
19. op2<0, x, 1, x, lsr>, c = 1, rs < 32 -> rm shifted rs y c = 1.
20. op2<0, x, 1, x, lsr>, c = 0, rs < 32 -> rm shifted rs y c = 0.
21. op2<0, x, 1, x, lsr>, c = 1, rs = 32 -> 0 y c = 1.
22. op2<0, x, 1, x, lsr>, c = 0, rs = 32 -> 0 y c = 0.
23. op2<0, x, 1, x, lsr>, c = any, rs > 32 -> 0 y c = 0.

24. op2<0, x, 0, 0, asr>, c = any, shiftamount = 0 -> rm y c = any.
25. op2<0, x, 0, 0, asr>, c = 1, shiftamount < 32 -> rm shifted shiftamount y c = 1.
26. op2<0, x, 0, 0, asr>, c = 0, shiftamount < 32 -> rm shifted shiftamount y c = 0.
27. op2<0, x, 0, 0, asr>, c = 1, shiftamount >= 32 -> rm shifted shiftamount y c = 1.
28. op2<0, x, 0, 0, asr>, c = 0, shiftamount >= 32 -> rm shifted shiftamount y c = 0.

29. op2<0, x, 0, 0, ror>, c = any, shiftamount == 0 -> rm y c = any.
30. op2<0, x, 0, 0, ror>, c = 1, shiftamount >= 32 -> rm y c = 1.
31. op2<0, x, 0, 0, ror>, c = 1, shiftamount < 32 -> rm shifted shiftamount y c = 1.
32. op2<0, x, 0, 0, ror>, c = 0, shiftamount < 32 -> rm shifted shiftamount y c = 0.

Gracias a estas pruebas, he detectado problemas en la recuperación de funciones de la lut 24, 29 y 30.
Los tres casos pertenecen a i = 0 bit4 = 0 `shift_amount` != 0 ? y pero en la instrucción sale como `shift_amount` == 0.
Es decir, le estamos pidiendo hacer una operación para la en teoría no debería ser capaz.
Esta es una errata de copiar y pegar 999 test. Es más de hecho vemos que en esos test no hay concatenación de SHIFT_AMOU de ningún tipo y por lo tanto es 0. Además hay que sumarle que un número de 5 bit no puede exceder los 32. Esta condición ocurre cuando I=0, Bit4=0 porque tiempre será 0 siempre que lo hiciese. Estos dos últimos comentados por lo tanto 

He optado por optimizar mejor el código de operand2 para aprovechar mejor la comprobación de bit4 y suponer inmediatos de 5 bits y utilizando rotaciones estándar. He apalicado estrategias de adelantar o atrasar y simplicación de código común. Además con suerte la arquitectura del procesador a la hora de cargar el `shift_amount` tenga un flag automático de Z como ARM (recursivo). 

Aquí sinceramente me he asegurado que los diferrentes provedores de IA, digan si es una implementación certera, pedí ayuda para los casos pero son puñetero desastre. He cogido papel y lápiz y me he puesto a dibujar un grafo de CFG para tenerlo a mano y dejarme de tonterías. Y de paso así no me engaño por la sintaxis de las variables y voy straight forward. Considero que este es también uno de los aspectos que generan confusión. En esta ocasión no he considerado el carry como una salida boleana 

# 22 de julio

Parece que la cosa se ha alargado y he terminado de probar esto hoy.

<operand2.pdf>

Quiero remarcar que ha sido muy importante revisitar el código desde el POV de probar las cosas, porque considero que ahora tengo las ideas más claras de como va porque he visto más plausible optimizar ciertos aspectos que no había visto anteriormente. Tales aspectos que he replanteado en no implementar otra lut a futuro para cada caso de rotación. Creo que optimizarlo y dibujarlo antes ha sido claro para ver donde estaban los fallos.

Muchas cuestiones son de lógica que evaluándola podemos estar simplificando redundancias.

Vamos con la planificación.

1. Probar operaciones de arm fsr. (hoy)
2. Luego si esto va, crear una lut iniciar parcial para saber como direccionar estas operaciones. (hoy-mañana)
3. Probarla. (mañana)
4. Diseñar un esquema básico de memoria con chip. (mañana + 4 días)
5. Preparar estado del arte
6. Preparar preguntas y reunión.

Procedamos con los puntos 1 2 y 3 juntos. Creo que es una buena estrategia de integración como hicimos antes.

Lo primero que procedí a realizar es revisar posibles huecos en le implementación genérica. A parte de los caveats que y conozco como la lectura y escritura de pc. Sin embargo este aspecto es el que menos preocupe pese a que falte comprobar, lo cierto es que en el futuro podemos gestionar este caso cuando tengamos el flujo funcionancionando.

En esta ocasión vamos a adoptar una estategia un tanto diferente de comprobar. No vamos a comprobar siempre lo mismo.
Empezamos por una comprobación exhaustiva en donde buscaremos ir cada bifurcación. CON EXCEPCIÓN de no pasar por el bloque de perform operation, porque generaría una combinación loca de casos a probar. Y luego comprobaremos la combinación loca pasando una vez para comprobar el acceso a lut y el estado de pc con parametrizados. En esta segunda fase de chequeos, no interesa comprobar tanto sus caminos así como sí interesa ver cada operación y su resultado así como sí ha podido cambiar las banderas correctamente.

Tampoco vamos a considerar comprobar las banderas de forma conjunta porque esto daría otra combinación peligrosa de casos. Este código a diferencia del de operand2, no tiene tantas bifurcaciones por lo que valdrán pocos casos completos para la primera fase.

Sin embargo debemos construir la lut parcial, antes.

Empecemos por lo de siempre, analizar qué variables tenemos a simplificar.

opcode tiene 4 bits -> 16 combinaciones.
s es 1 bit -> 2 combinaciones.
rd_pc es 1 bit -> 2 combinaciones

El hecho de considerar los 4 bits de campo de registro destino como un booleano fue motivado por el tratamiento de casos especiales. Esto es posible porque el campo rd es fijo tiene siempre el mismo significado sin que pueda variar y desenbocar en casos.

Sin embargo y dado que tenemos una combinación de 48 + 8 casos resulta que para poder identificar inequívocamente esos 56 casos precisamos de como mínimo de 6 bits como mínimo para diferenciar esos casos. Cosa la cual ya cubrimos con esos 4 + 1 + 1 bits de variables. Entonces queda ahora organizar las funciones dentro de la lut. Excepcionalmente conincidirá en gran medida en el orden en el que se muestran, puesto al poco cambio que hay que hacer. 

Cabe resaltar que este cálculo es así porque no tenemos variables que colisiones y/o que dependan entre ellas como sí ocurría en operand2. 

Otra mejora a futuro consistiría en reducir las luts, juntándolas. Por ejemplo: AMD FSR y cómputo de operand2. Esto es demomento bastante plausible puesto que si confirme al buen desarollo del progama, vemos que la única dependencia, podríamos considerar su fusión. Aunque bajo este prisma, cabe resaltar que esto resulta en una clara fragilidad para las pruebas unitarias si lo hacemos a lo bruto. Aunque a cambio obtendríamos un código con los mínimos saltos. Pero en oposición tendríamos un bloque de código infernal de mantener. 

Propongo que en el futuro traslademos los códigos de plantilla de operand2 junto a los de fsr. Pero a la hora construir la plantilla de fsr construyamos dentro la plantilla operand2 y mantengamos operand2 para las pruebas. Ahora bien hacer esto implica que deje de tener sentido tener una lut de operand2 porque no es código que vaya a producción. 

Ello pese al "atractivo", puede tener penalizaciones en el binario final como problemas de caché o tamaño del binario final.
Porque combinar 6 bits + variables de operand2 puede dar lugar a una combinación radioactiva de casos a considerar.

Pero esto ya será para el Ivan del mañana.

Lo que vamos a hacer es a extraer las variables y juntarlas en en código para que quepan en 1 << 6.

Vale hecho.

Como afrontamos hacer el test: Yo diría que la misma manera. Parametrizados. Porque ya realiza todas las comprobaciones pertinentes al momento. Voy a hacer el grafo para ver qué pruebas hacer.

Luego lo adjunto. Pero he tenido tenido que aplicar algún refactor para garantizar mejor lectura de código. Luego también he utilizado para usar put_raw.

Por otra parte he decido añadir despliegue automático en github para facilitar al tutor la revisión de pruebas...
Le he pillado el truco a hacer test parametrizados porque resultan muy eficientes de construir.

<cfg_fsr.pdf>

# 26 de julio

Bueno, hoy es el último día anterior a la reunión con Fran. Ayer tomé el día libre para despejarme un poco y salir a recorrer la ciudad. Sin embargo, en todo ese trayecto he estado planteando el diseño de la memoria. Aunque no llegué a nada concluyente porque me quedé en qué información persiste en el bus de memoria.

En un principio, mi idea de cómo implementar el bus de memoria es utilizar la abstracción de la lut. Puesto que proporciona las herramientas necesarias de normalización de índices para el enrutamiento de direcciones. Desde este punto de vista el bus no solo sería un mero enrutador sino que ahora podríamos dar una interfaz de funciones relacionadas con la gestión de memoria.

Pero claro, según lo que pensado es que necesito una inicialización previa. Y aunque es cierto que podemos hacer un singleton y precocinar los datos con un consteval en tiempos de compilación.

Ahora bien, qué almacenamos?

Supongamos que un chip de memoria es sí en realidad algo variable. Algo de lo que podamos sacar variantes de la misma cosa. Es decir que es heredable con sistema de clases, objetos e instancias. Y con métodos si acaso abstractos para dejar muy claro que no es instanciable directamente.

En c++, no podemos guardar abstractos estáticamente y tampoco implementarlos de forma ad hoc. C++ solo trabaja con tipos concretos. Pero podemos trabajar con punteros de tipos concretos y de tipos abstractos. Esto es lógico por la forma en la que pudésemos implementar con c. El tradeoff de este mecanismo es la indirección, para acceder al método de un chip de memoria tengo que pasar por bus de memoria luego dar la memoria demandada y accionar un método que debe ser averiguado cual es. Esto es la típica consecuencia de usar punteros.

Si vemos cómo se hace en C, quizás podamos entender mejor cómo son los métodos virtuales. Para hacer OOP en C típicamente se hace este código. Aunque en el fondo no se aleja mucho de lo que en el fondo hace c++.

``` c

// C23

struct A {
	int number;
	char s;
};

char getS(struct A* this) {
	return this->s;
}

void setNumber(struct A* this, int number) {
    this->number = number;
}

// código cliente.

struct A a = {69, 8}; 
constexpr auto s = getS(&a);
setS(&a, 42);

```

Este es un código complemente válido para el estándar de c. Vemos aquí el modo de usar métodos: nos obliga a conocer la referencia/puntero del objeto con que queremos interactuar por cada método. Esto puede ser más o menos conveniente la sintaxis, pero el concepto es el mismo. Ahora planteemos ¿cómo haríamos herencia?. Cabe recalcar que c++ permite herencia múltiple. En el heredado, vamos añadir un método y una propiedad.

Para reflejar extresamente que es una herencia (no vale reescribir A):

``` c

// C23

struct A {
	int number;
	char s;
};

char getS(struct A* this) {
	return this->s;
}

void setNumber(struct A* this, int number) {
    this->number = number;
}

struct B {
	struct A a;
	int q;
};

void metodo1(struct B* this) {
	this->q += this->a.number;
}

// código cliente.

struct B b = {{69, 8}, 1}; 
constexpr auto s = getS(&(b.a));
setS(&(b.a), 42);
metodo1(&b);

```

Bajo implementación ya vemos que aparecen incovenientes de sintaxis muy serios. Siendo que es obligatorio que el cliente conozca la estructura interna para saber a qué método llamar. No podemos hacer otra forma porque en c una función se distingue por su nombre y no por sus parámetros como sí ocurre en c++. De hecho, en el fondo c++ trabaja así pero oculta el mecanismo de obsfuscación de nombres. Siendo que en realidad cuando hacemos b.setB en realidad ese método es un `setB_didjqi2hfibiu3iuf2hf` que hace lo de a pero conviertiendo a a lo que interese. De hecho a este problema se le conoce como name mangling. C++ incrusta en el binario pseudo nombres de las funciones que necesite. Por eso, típicamente para garantizar la interoperabilidad con otros lenguajes desde c++ se permite usar un extern "C". De hecho la herencia múltiple tiene también una crítica muy consistente y es que su manejo se hace por nombres y tipos de atributos. Siendo que puede haber problemas si heremos dos clases que tengan misma signatura y nombre. Aunque creo que por ese motivo tenemos el resolutor de ámbito. Pero si no conocemos las implementaciones a fondo, es posible que omitamos de largo este problema. En cambio, en C el manejo de esta serie cuestiones es base a ser más explicito: teniendo que indicar el método a que invocar y según a qué parte aplicar.

Una forma de hacer interfaces es:

``` c

struct IElement {
    const char* (getText)(*)();
    void (setText)(*)(const char*);
}

```

Pese a lo que pueda parecer de primera vista, esto actua más como una colección de funciones que podemos asignar o cambiar por otras a nuestra conveniencia que una clase al uso, puesto que pierde el contexto variante de this. Que se podría añadir pero quedaría limitado a un tipo en concreto. En contraposición, este mecanismo sí nos permitiría reciclar signaturas pero deberemos antes crear una función sin colisión.

Bueno que al caso, qué vamos a meter dentro de nuestro bus? Memoria. Bien. ¿Cómo? con punteros.

A la hora de trabajar con punteros en c++ tenemos varias opciones:

- `reference_wrapper`: referencias no nulas
- punteros crudos: tradicional
- `unique_ptr`: puntero con semática de propietario
- `shared_ptr`: puntero con semática de propietario múltiple

la primera de las opciones ofrecidas por el lenguaje es la menos atractiva puesto que obliga inicializar todo en el contenedor por defecto al menos. No admite nulos. Cosa que en una primera intancia no interesa perder porque estamos haciendo la implementación por pasos y podemos no completarla toda de una. Además con la contrucción por defecto de nulos podemos darle un significado.

los punteros crudos son lo más genérico con menos restricciones.

`unique_ptr` es un candidato muy bueno pero no admite memoria hermana que nos puede interesar para reflejar que ciertas partes de memoria pertenecen al mismo chip.

`shared_ptr` es una opción interesante puesto que internamente maneja las intancia activas.

En ambos casos cuando ya la referencia al bloque no se puede usar, automáticamente el destructor es accionado. Lo cual resulta convenientemente cómodo sin escribir destructores. No obtante, añade overhead que puede penalizar en tamaño y rendimiento.

Bien.

Creo que iremos con los puteros crudos porque considero que podemos emular muy bien siguiendo las restricciones impuestas. La semántica de propietario la podemos hacer verbal, siendo que solo en el bus de memoria de pueda destruir o crear cuando toque y siempre va a ser través de este la interacción de la cpu y otros componentes. Bus de memoria es el experto de información en direccionamiento. Y dada esta naturaleza y el uso de la abstracción de la lut, podemos ahorrarnos algo de overhead reutilizando procedimientos de la lut. Podemos incorporar mecanismos de seguridad contra double free, preguntando cuantos punteros hay iguales en la lut, borrar y luego pedirle a la lut que los remplace por nulos. Además de que en la gba hay huecos vacíos sin usar. 

Creo que es un mecanismo muy robusto.

Ahora plateemos como será la interación de lectura y escritura.

En sí, el bus de memoria es algo que existe y sirve para interconectar. En "preproyecto", hice un sistema de memoria pero resultaba muy desastre, porque tenías el bus en la cpu. Y luego otra estructura que era la información del bus que llegaba a las memorias. Es como si fuera el bus de la cpu exclusivamente, y ello derivaba en un problema de incoherencia de interfaces. Sin embargo, vamos a plantearlo diferente.

Debemos pensar que cuando hablamos de un chip de memoria no siempre podremos realizar las mismas operaciones. Dudo mucho que algún componente chip pueda escribir en la cpu. Porque sí la Cpu es una memoria muy especial que solo ella puede escribirse a sí mismo, pero el resto no puede escribir en ella. La cpu solo pide y le dan. La cpu es maestro y el resto esclavos. Pero tampoco es del todo así. La cpu por memoria lo único que tiene son registros. Pero tampoco el resto son del todo esclavos si tomamos en consideración el dma. En este último no vamos a entrar.

Otro ejemplo que refleja esta extraña naturaleza de que es una memoria comunicada al bus pero no es una en sentido tradicional de un lista de bytes si vemos el uso. La PPU es el encargado de dibujar. Un contraejemplo es la WRAM que se trata de una memoria normal y corriente.

Entonces tenemos dos tipos de memorias: una tonta sin lógica (propósito: contener información) y otra vitamizada con código adicional. Pero todas ellas deben seguir las interfaces de memoria.

Pasemos ahora a la implemntación.



problema: añadimos al bus una memoria y esta es una supermemoria que quiere comunicarse con otra o autoescribirse porque es así de chula.

qué es mejor?

-variable global
-variable inyectable por parámetro.

interesa que al memory bus le metemos una memoria y queremos desde la memoria escribir a otra dirección de memoria (otro chip o a no nosotros mismos)


evidentemente, es de primero de informatica que la segunda: testing y declaración de comunicación

he usado lut en lugar de array por vitaminar la estrutura con métodos que creo que pueden ser convinventes.

problema: la lut y array incrusta el tipo de dato como array<1> != array<2>. 
ojo que -flto es una optimización que trata de eliminar la desvirtualización si es usada una vez solo.

solución: no me importa, no merece la pena dar variabilidad a esa cosa, porque solo habrá una y será la de gba.

IMPOTANTE:

dado que memory bus maneja putneros todo lo haya dentro si está en el heap va a estar todo ahí si es variable y da igual . que -> porque ocupan lo mismo


añado métodos de búsqueda, iteradores. Así nos alineamos al estándar de la biblioteca std.



``` c++


  virtual u32 read(u8 size, u32 addr) const override { return int_read<size>(addr); }
  virtual bool write(u8 size, u32 addr, u32 contents) override {
    return int_write<size>(addr, contents);
  }



// versus


virtual u32 read(u8 size, u32 addr) const override {
  switch (size) {
    case 8:  return int_read<8>(addr);
    case 16: return int_read<16>(addr);
    default: return int_read<32>(addr);
  }
}

virtual bool write(u8 size, u32 addr, u32 contents) override {
  switch (size) {
    case 8:  return int_write<8>(addr, contents);
    case 16: return int_write<16>(addr, contents);
    default: return int_write<32>(addr, contents);
  }
}

```

porque size debe ser conocido en tiempo de compilación.!!! debe ir un imediato entre `<>` y no una variable en tiempo de ejecución. ¿bulo sobre que pueda ejecutarse en tiempo ejecución y recutilizar las funciones construidas y dar cabida a una indirección o lut?

otro error que desconocía de c++ es que para funciones virtuales hace falta poner el destructor aunque no haga absolutamente nada, y exigir que sea por defecto explícitamente.

external linkage -> problema con lambdas porque si clase { - template<lambda> } el lincado de ese interno lambda genera confusión sobre generar código. El estándar exige que el lincado dependa de factores externos enlugar de algo interno como dentro namespace y dentro de una clase y enluvuelto de lambda.  


ACABO DE ACORDARME QUE PUEDES USAR COMAS PARA SEPARAR NÚMEROS EN BINARIO, HEX. Me acordaba de forma de rust que era con _ pero ahora caigo que en C23 también incluyeron eso concretamente. 

# 5 de agosto

Tras una semana y pico de "descansito" vuelvo al TFG. He tenido ya primera reunión. Hay que corregir y avanzar en la memoria del tfg. Pero de momento, me gustaría dejarlo un poco para el final porque quiero empezar retomando la parte de implementación. Primeramente aplicando algunas de las sugerencias que me ha dicho Fran en esta reunión.

Una de las sugerencias es hacer que  sea más idiomático:

  ``` c++
  /// lut.hpp
  template <typename... Args>
    requires std::invocable<store_t, Args...>
  constexpr decltype(auto) invoke(std::size_t idx, Args&&... params) const {
      return get(idx)(std::forward<Args>(params)...);
  }
  ```

siendo que se utilice `std::invoke`. Este mecanismo resuelve llamadas más generales.

Habrá alguna que otra cosilla más pero de momento quiero ya empezar a aporrear teclas que pienso que es lo más fácil para retomar el hábito.

Los objetivos que hemos definido para la siguiente reunión es:

De desarrollo

- Ciclo de ejecución de la CPU funcional
  - Fetch-Decode-Execute
- Añadir las instrucciones de carga (para que no sea necesario settear a mano los registros).
- Ver cómo funciona el DMA

Hasta ahora tenemos hecho esto:

- ALU lógicas del modo ARM.
- Memoria con clases.

Bien, vamos a razonar el orden de como vamos a hacer esto. Veamos. El ciclo de ejecución de la CPU funcional es una cosa que depende fundamentalmente otras cuestiones a comprobar: 1) que el valor de PC sea el correcto para cada instrucción, 2) ¿cómo inicializar y terminar el flujo? 3) Si al dar el salto, ejecuta lo del salto 4) El acceso a memoria para la recuperación de instrucciones. Siendo que la 4 es una cuestión relacionada con la memoria. Además el segundo aspecto de "Añadir las instrucciones de carga (para que no sea necesario settear a mano los registros)." es también dependiente de 1) lo bien que esté implementada la memoria y de 2) las instrucciones y decodificación del opcode.

Sin embargo el DMA es el único que depende de exclusivamente de la memoria. Empezaremos por este al tener menos dependencias.


https://gbadev.net/tonc/dma.html
¿que es el dma?
El acceso directo a memoria es un controlador que es utilizado para la transferencia rápida de datos de una memoria a otra. DMA toma el control del bus de memoria, efectúa las operaciones de memoria pertinentes y devuelve el control a la CPU.

Existen 4 canales de DMA:
- 0: el de más alta prioridad, CPU <-> IWRAM.
- 1 y 2: Sonido.
- 3: el de menor prioridad, para propósito general.

En la teoría la CPU para indicar que quiere utilizar el mecanismo de DMA debe indicar los datos al controlador:

- Destino `REG_DMAxDAD`
- Origen  `REG_DMAxSAD`
- Cantidad
- Cuando

El controlador DMA tiene registros para indicar estos campos. El registro de control `REG_DMAxCNT` indica la cantidad a transferir y otras habilitar otras características del DMA. Indicando la actualización de las direcciones de destino y fuente después de cada bloque transferido

Pese a que todos sean de 32 bits, el registro de control es usual verlo dividido en dos de 16 bit. Siendo dos usos uno para el control como tal y otro para cantidad de transferencia. 

| 31   | 30  | 29, 28 | 27 | 26   | 25  | 24, 23 | 22, 21 | 20 .. 16 | 15 .. 0 |
|------|-----|--------|----|------|-----|--------|--------|----------|---------|
| `En` | `I` | `TM`   | -  | `CS` | `R` | `SA`   | `DA`   | -        | `N`     |

Deglosando tenemos que

- `N` es el número de iteraciones a transferir.
- `DA` ajusta la dirección destino. Pudiendo significar:
  - `DMA_DST_INC` (00) incrementa tras cada transferencia. 
  - `DMA_DST_DEC` (01) decrementa tras cada transferencia.
  - `DMA_DST_FIXED` (10) fija
  - `DMA_DST_RELOAD` (11) incrementa y restablece registro al finalizar.
- `SA` ajusta lo mismo que `DA` pero apara la dirección fuente.
  - No tiene (11).
- `DMA_REPEAT` repite las transferencias por cada VBlank o HBlank según el timing.
- `CS` indica el tamaño del bloque a transferir (32 si está en 1) si no es 16.
- `TM` especifica cuando transferir.
  - `DMA_NOW` (00) inmediatamente.
  - `DMA_AT_VBLANK` (01) al inicio de VBlank
  - `DMA_AT_HBLANK` (10) al inicio de HBlank
- `DMA_AT_REFRESH` (11) sin uso en la gba
- `I` Interrumpir al terminar.
- `En` Habilitar DMA para este canal.

Modo de Timing,¿Cuándo inicia?,Comportamiento sin DMA_REPEAT,Comportamiento con DMA_REPEAT
Immediate (00),Al instanciar DMA_ENABLE,Realiza N copias de golpe y se desactiva.,Ignorado / No tiene sentido práctico.
VBlank (01),Al inicio de la sincronía vertical,Realiza N copias de golpe durante el VBlank y se apaga.,Realiza N copias en cada frame (útil para actualizar OAM/Sprites).
HBlank (10),Al inicio de cada línea horizontal,Realiza N copias de golpe en el primer HBlank y se apaga.,"Se dispara en cada línea, copiando N elementos por línea."
Special (11),Evento de hardware (ej. FIFO de Sonido o Display FIFO en DMA3),Transfiere bloques de audio/vídeo a medida que el hardware los solicita.,Mantiene el flujo de audio/vídeo constante en segundo plano.


Vale. Cambio de planes esto es demasiado complejo.

Mala decisión haber empezado por aquí vamos a continuar por una parte interesante como lo es el ciclo de vida del programa Fetch-Decode-Execute. AL fin y al cabo la lectura de instrucciones no se hace por DMA. Aunque puede ser de interés trabajar con la caché.

Empecé por definir estas funciones en la cpu!

``` c++
void set_arm_mode();
void set_thumb_mode();
void step();
```

De forma que eliminemos el overhead de comprobar por cada instrucción si estamos en modo thumb o no.

``` c++
void arm7tdmi::reset() {
  this->empty_registers();
  this->write_cpsr(I | F);
  this->set_mode(MODE_SVC);
  this->set_arm_mode();
  this->write_pc(EXCEPTION_RESET);
}

void arm7tdmi::set_arm_mode() {
  this->instruction_size = 32;
  this->instruction_incrementator = 4;
  this->execute = execute_arm;
  this->clear_cpsr(T);
}

void arm7tdmi::set_thumb_mode() {
  this->instruction_size = 16;
  this->instruction_incrementator = 2;
  this->execute = nullptr; // dumb!
  this->set_cpsr(T, T);
}

void arm7tdmi::step() {
  auto current_pc{this->read_raw_register(pc)};

  auto inst{this->bus->read(this->instruction_size, current_pc)};
  this->write_pc(current_pc + this->instruction_incrementator);

  std::invoke(this->execute, *this, inst);
}
```

Ahora he decidido que `read_pc` y `write_pc` no sean solo atajos directos a la interacción de registros sino que contengan las restricciones necesarias del modo de cpu en el que estén. Alineamiento y si se usan en como fuente de instrucción.

Ahora si quiero leer un valor en crudo del pc están las operaciones del estilo `*_raw_*`. Reflejando mejor este propósito.

Ahora tengo que arreglar los test para que no fallen por este motivo.

He decidido reorganizar los extractores field porque creo que pueden utilizarse en el futuro como en DMA. He aprovechado para meter métodos auxiliares.

# 9 de agosto

Volvemos a la carga tras algo de inactividad. Dado el poco tiempo que tengo ahora para esto porque lo voy a dedicar en ocio. He estado pensando en refactorizar algunas cuestiones antes de proceder con lo tocho.

Veámos la imagen completa:

- Tenemos como objetivos pendientes:
  - DMA
  - Carga/almacenamiento
  - Memoria
	
- Creo que tenemos una estructura bastante rara:

	``` text
/home/ibai/Projects/neogba/include/neogba/arm7tdmi:
  drwxr-xr-x. 1 ibai ibai    50 jul 21 12:22 .
  drwxr-xr-x. 1 ibai ibai    80 ago  5 19:53 ..
  -rw-rw-r--. 1 ibai ibai 26054 ago  5 20:23 arm_isa.hpp
  -rw-rw-r--. 1 ibai ibai  5019 ago  5 18:20 cpu.hpp
  -rw-rw-r--. 1 ibai ibai 13678 ago  5 20:23 isa.hpp
	```

	-  La cual creo que sería muy conveniente dividirla.
	- `isa.hpp` realmente contiene constantes y métodos de ayuda.
	- sin embargo, `arm_isa.hpp` es todo un monstruo que tiene lógica de tablas, creación de funciones, plantillas.
		- es como que este archivo aglomera demasiadas cosas.
		- siendo que al paginar el archivo de una pasada complica que seguir el rastro al depurar un error.

- Por tanto creo, que es necesario refactorizar esto para una disposición más cómoda.
- No obstante y pese a realizar este cambio no nos podremos librar de algunas funciones para ocultar la implementación y exponer interfaz necesaria.... 


¿En qué exactamente va a consistir el refactor?
- `isa.hpp -> isa/constants.hpp` 
- `arm_isa.hpp -> isa/arm_mode/operand2.hpp` solo tendrá todo lo relacionado (plantilla y tabla rellenada).
- `arm_isa.hpp -> isa/arm_mode/fsr.hpp` solo tendrá las operaciones de fsr (plantilla).
- `arm_isa.hpp -> isa/arm_mode.hpp`  solo será una tabla y execute arm

¿porque operand2 tiene la tabla también? fácil. operand2 solo tiene el propósito de hacer operand2. Y exclusivamente eso. Operand2 solo lo usa fsr. mientras que fsr se utilizará en conjunto con otros tipos de instrucciones.

Ahora toca arreglar errores otros para que se pueda usar de esta nueva forma.

Vale. Cmabio de planes.

He pensado en concentrar ambos sets de instrucciones thumb y arm en uno solo include. siendo que hacer `#include "neogba/arm7tdmi/isa/include.hpp"` sea suficiente para hacerse a todo el sistema.

Por qué hacer esto?
Por que así solo se ven los executes de ambos modos. Y evitar así toda la morralla de luts, 30000 funciones.
Y luego por cada isa particular definir la lut autoevaluada y definir el execute en un fichero para delimitar sus responsabilidades.

claro pero hay un problema.

Y es que nuestro mocking lo hacemos mirando en la tabla lut por lo que deberíamos exponer de alguna forma esto para testing.

``` c++
// arm_fsr_test.cpp
ASSERT_EQ(params.caller, arm_lut.get(inst));
```

Pues fácil, esa evaluación se realiza en una cabecera que importaremos en el cpp del execute Y así podemos seguir siguiendo la regla que de que un cpp reciba el mismo nombre que su cabecera principal. Porque? Porque así no diferimos en nomenclatura arm_mode.cpp de include.hpp.

El siguiente paso será implementar las instrucciones de carga y almacenamiento. Adicionalmente me gustaría hacer un cambio en implementar la comprobación del campo condicional del modo arm. Además me gustaría hacer las implementaciones de las instrucciones lógicas y aritméticas y las carga-almacenamiento del modo thumb. por ir a la par.

Luego mi plan es centrarme en la documentación a full. Y retomar algunos punto que se trataron en la reunión.

Y finalmente ir con el DMA. Pero creo que es bastante más complicado, porque implica hacer la sincronización vertical y horizontal correctamente. Además de averiguar que coño es eso. Pero que parece que es sobre los gráficos!!

Vamos, que estoy jodido por bocazas.

Bueno en tal caso sí es así consideraré cambiar el objetivo por otros: considero que aquí estaría muy bien implementar la instrucción branch and exchange para pasar de arm a thumb y viceversa e implementar más de ambos isa cómo la multiplicación.

Otra cosa que quizás vaya viendo es sobre el reloj y los ciclos por si acaso. Aunque siendo francos, y al ser este un proyecto amateur creo que podría permitirme omitir la relojería pero podría estar jodido si las pruebas que se requiera esto de la precisión de ciclos sea complejo.

En un aspecto que he estado pensando es en más general cómo funcionan los emuladores. ¿A qué no sería ideal que el programa antes de ejecutarlo lo podríamos preparar para la computadora de destino? es decir cogerlo entero y pasearse por este, mascarlo, y dejarlo ya para el ordenador listo para ejecutar nativamente. No creo, porque eso sería como un decompilador y compilar de nuevo. Pero además, pese a no tener el problema de las instrucciones de longitud variable y alineamiento, lo cierto es que el programa podría estar sujeto a condiciones de interpretación de bits en vivo para determinar si un espacio de 32 bits es una instrucción o dos de thumb. Ello quiere decir que deberíamos realizar algún tipo de análisis en observación de patrones para determinar una interpretación de datos de unos y ceros correcta. Aunque en tal caso de hacerse habría que analizar el riesgo de que ocurra que el compilar por listillo reutilice una instrucción de 32 bits como dos de thumb y que ambas tres sean complemente legales y legibles. ¿habrá alguno que haga esto por ahorrarse 32 míseros bits?. 

# 11 de agosto

Hoy vamos a centrarnos en lo realmente bueno.

1. Transferencia de Datos Simple (Word / Unsigned Byte) Aplica a LDR, STR, LDRB y STRB.
2. Transferencia de Media Palabra y Datos con Signo Aplica a LDRH, STRH, LDRSB y LDRSH.
3. Transferencia Múltiple de Bloque Aplica a LDM y STM.
4. Intercambio Atómico (Data Swap) Aplica a SWP y SWPB.

Entonces voy a sacar la documentación y vamos con la primera de las opciones.

Pero antes lo que voy a hacer es que en el execute del modo arm funcione el cond e implementar una función dummy para thumb de momento.

Ahora centrándonos en lo que nos acontence, tenemos que single trans tiene hasta 6 banderas en forma de bit que definen un comportamiento u otro. Para empezar tenemos que en función de L decide si es un almacenamiento o carga, W si writeback en rn, B si es un bytes o no, P si es sumar o restar a base (pre o post indexado) e I es si es inmediato o el temible offset desplazado. 

Con esta información creo que es suficiente para colocarla en la template.

Tal y como suponía que r15 será algún tipo de caso especial. 

Si es r15 en rn, W estará desactivado.
Jamás r15 será en rm (offset desplazado).
Si r15 es rd y es una instrucción de almacenamiento, el valor almacenado será la dirección + 12.

Por lo tanto, volveríamos a obtener una combinación exclusiva de casos.

saber si r15 es una cosa que podríamos saber antes puesto que está en un sitio campo fijo rd de 4 bit. Además muy seguramente coincidirá con el resto de formatos de instrucción por el hecho de no tocar las narices de hacer la misma comprobación en 32 sitios distintos y ahorrar así en circuitería.

si I es 1, vemos que claramente reutiliza la lógica de bit4 que ya hemos visto anteriormente. Por lo que no voy a hacerla, vamos a reutilizarla. Esto es una clara suposición dado la autoreferencia de la documentación y asumiendo ahorro en la circuitería. Aunque creo que podemos utilizar directamente la lut operand2 para ese caso. Siendo así de elogiar por no haber optado por realizar una combinación termonuclear y preferir la reutilización. El truco aquí es tener cuidado.

Vemos que operand2 también considera valores fuera de sus 12 bits. (I, Rd). Sin embargo, la buena noticia es que ambos campos siguen coincidiendo aquí. Esto es un claro fruto de la ingeniería del diseño del chip eficiente. Y ahora el esfuerzo ha dado sus frutos y tenemos un camino más fácil de implementación. Esto sugiere que en el futuro será muy costoso mantener los cambios si decimos hacer la combi explosiva.

Siendo que no tenemos que hacer ningún hack raro para reutilizar esta mecánica de solución. Esto tiene bastantes garantías, puesto a que el funcionamiento de operand2 ya fue probado suficientemente y además conocemos su funcionamiento (aunque sea vagamente y recordando la idea que hay detrás más que la exactitud)

Seguimos con algunos más sencillo. Como saber si es carga o almacenamiento o una palabra o un byte.

Podemos simplificar el código operadores ternarios en línea y ser compile time. Not every true por si acaso.
Casos especiales rn = rd.

Vale ya ya está implementado. Y tenemos otro problemita. Y es que tener 7 variables de plantilla, tenemos una posbilidad de 2^7 combinaciones a prestablecer. Lo cual resultaría en insertar a mano 128 funciones. Sin embargo, pensemos por un momento: típicamente una instrucción del modo ARM está compuesta por el campo condicional y no inmediatamente después el resto de sus campos necesarios. Es decir existe un hueco fijo de instrucciones. Que no servirán para absolutamente sino que solo sirva para su identificación. Pero no siempre es así. Puede ser que tengamos bits por medias de indentificación. Como mismamente halftrans. Bueno aunque puede ser bastante variable.

Vale para la inserción no habrá problema alguno porque su pueda hacer con ifs. Pero a la hora de indexación y búsqueda del recurso esta práctica desembocaría en una muy grave penalización de rendimiento por predicción de condiciones.

Pero que no tuvimos este problema antes? Pues sí, y aquí es donde entra la simplicación por karnaugh! La táctica es bien fácil.

Lo que podemos hacer es en lugar una lut dentro de una lut, utilizar una e ir computando el índice por partes. La primera parte consistiría averiguar a qué tipo de instrucción es. Luego de ahí se obtiene un índice en función del tipo.

Tenemos otro problema si optamos por no escribir a mano y es que perdemos calidad en los test por consistencia ya que no seríamos capaces de estar al 100% de que lo devuelto por la lut se corresponda a algo externo. Esto es que, no podemos hacer un mocking comparando punteros función.

Aunque no obstante, creo que c++ tiene propiedad interesante con las funciones meta generadas. Y es que si bien es cierto que al insertar una función metagenerada con parámetros x en una lut, y luego volver a solicitar la ganeración de la misma función para el mock casero al menos con los mismos y exactos parámetros x debería ser el mismo puntero función. Lo cual tendría todo el sentido porque la función es una cuestión de código exacto para todas las veces que se llame y no tendría mucho sentido persistir en su sección de código dos copias de un código. A no ser que este tipo de cuestiones dependa del nivel de optimización, si utiliza un yield, una corutina asíncrona, o persiste en esta llamada la definición de la variables estáticas que deban ser persistidas entre llamadas.

Eso sí, los parámetros de plantilla deberían ser conocidos en tiempo de compilación. porque lo cierto es que no en tiempo de ejecución es absolutamente indicarle al lenguaje el tipo. 

Hagamos una prueba de concepto. Para ver si nuesto caso de uso de uso plantillas funciona tal y como debe.

"""

supón que estás en c++26 para gnu linux x86 utilizando g++ sin extensiones de vendor.



tenemos una super plantilla que admite 4 variables de tipo booleano de plantilla (tparam).



template<bool a, bool b, bool c, bool d> f(int codigo) {...}



y nos interesa generar todas la combinaciones posibles de esa plantilla. Pero ojo, es demasiado como para hacerlo a mano... 

De forma que la función f la utilizaremos a través de una lut como intermediario que en función del código decidirá si ejecutar con unos parámetros de plantilla u otros.

Seamos francos, nos suda absolutamente como se llamen esas funciones finales. Lo importante es que aparecezcan bien insertadas en la lut.

Para garantizar la calidad de nuestros testing desde la lut, buscamos hacer test del estilo en los que montamos un código y vemos que llame a función correctamente. Como una especie de mocking pero casero por simplificación. Desde sentido, 

1. Si la lut almacena copias datos de la signatura (void f(\*)(int)) ¿es posible? ¿tendremos datos binarios de la función por duplicado? ¿o solo los punteros?
2. ¿Es posible que si utilizando Google Test para C++ podamos comparar si la lut redirecciona bien recuperando su puntero función metagenerado de la lut y compararlo con la misma función vuelta a ser instanciada desde la plantilla con los mismos parámetros de esperados adhoc? En otras, ¿es cierto que mylut.get(0001) == f<false, false, false, true>? 

"""

Vamos a crear una test para la prueba de concepto.

``` c++
#include "neogba/structs/lut.hpp"
#include <gtest/gtest.h>

using namespace neogba;

template <bool a = false, bool b = false, bool c = false, bool d = false>
bool superplant(int codigo) {
  return (a << 3 | b << 2 | c << 1 | d) == codigo;
}
using function_type = bool (*)(int);
using lut_type = lut<function_type, 16>;

template <std::size_t I> constexpr function_type expected_function() {
  static_assert(I < 16);

  return &superplant<(I & 0b1000) != 0, (I & 0b0100) != 0, (I & 0b0010) != 0, (I & 0b0001) != 0>;
}

template <std::size_t... I> constexpr lut_type make_lut(std::index_sequence<I...>) {
  lut_type result;

  (result.fill(I, 0, expected_function<I>()), ...);

  return result;
}

TEST(proof_of_concept, template_functions_check_if_runs_match_adhoc) {
  auto mylut{make_lut(std::make_index_sequence<16>{})};

  EXPECT_EQ(true, mylut.invoke(8, 8));
  EXPECT_EQ(false, mylut.invoke(8, 9));
  EXPECT_NE(mylut.get(11), mylut.get(10));
  EXPECT_EQ(superplant<true>, mylut.get(8));
  EXPECT_EQ(superplant<true>, superplant<true>);
}

```

La prueba resultante es bastante simple y pasa satisfactoriamente las expectativas impuestas. Por lo que es positivo hacer este cambio de las funciones.

La única pega es el código de pruebas se más sensibles a cambios si llegasen a variar los argumentos de platilla. Cosa que en este caso sea muy poco probable y si se hiciera pudiésemos optar por técnicas como argumentos por defecto. No obstante, quizás tenga ventaja más estética que funcionar, pero la sintaxis de una función debería ser consultada y no es tan obvia si vemos que es lo que realmente hace solo por leer el nombre. Esto creo que realmente si puede ser un dolor de cabeza puesto que en los parámetros de plantilla hay veces en las que hay lógica negativa, poner true -> en realidad es asumir 0 en un campo cuando la convención habitual es true -> 1 o la aplicación de lógica como not algo algo.

Por lo tanto podemos concluir que esto sí podemos hacerlo. Siendo así que podemos reducir el código a mantener. Y eso es una gran ventaja.

Esta pequeña prueba de concepto para familiarizarme para metagenerar funciones. 

Notas para mí:

``` c++
make_lut(std::make_index_sequence<16>{}) // las llaves aquí son de constructor/inicializador, -> "()" == "{}"
                          |
                          V
make_lut(std::index_sequence<15, 14, 13, ..., 3, 2, 1, 0>)


tipo... i // variádico
i... // expansión 
```

Ahora aquí viene la siguiente pregunta como juntamos fsr y single trans en una lut. Pues es jodido.

Bueno primero lo vamos hacer de forma consistente, y vamos a aplicar este hallazgo a fsr. Bueno no.

Vamos a pensar en como podemos juntar todo esto en una sola cosa grande.

Perdón. Tengo otra idea que puede llegar a cuajar. Aunque es poco estándar y quizás requiera algo de macros. La cuestión es que para mejorar la fina legibilidad del código en los parámetros hubo una forma en swift que impusieron conocer los parámetros. Y aunque sea algo tedioso conocer la implementación concreta de una llamada lo cierto es que no fue para nada una idea mal encaminada. Porque así te aseguras que en futuras si requiere atención un cambio porque haya cambiado su signatura, el propio compilador te notifica de este cambio. Igual y tiene sus inconvenientes como tener que escribir cosas extras o el método no es infalible ante cambios con argumentos por defectos. O tampoco sirve si es un lamba.... Aunque pensándolo mejor, podemos aprochar el clangd para decirle que muestre los nombres de parámetros por nosotros.

es decir:

``` c++
// yo veo esto
inline constexpr auto arm_singletrans_i0_p0_u0_b0_w0_l0_rdpc0: void (*const)(arm7tdmi &, u32){arm_singletrans_generator<false>},

// y me gustaría                                                                                                        __
inline constexpr auto arm_singletrans_i0_p0_u0_b0_w0_l0_rdpc0: void (*const)(arm7tdmi &, u32){arm_singletrans_generator<i: false>},
```

Vale no se puede. Lol.

Bueno y es mentira eso de las macros en realidad sí se puede hacer. Y eso ya está funcando en los test. Y es una ventaja puesto que podemos ver como va. Y por medio de esto podríamos hacer plantillas con argumentos/paramétros bien definidos sin importar tanto el orden en el que estén definidos. Mierda! Esto es c++, y aquí el orden de inicialización sí importa. Vamos a hacer una cosa. Creo que hay un flag que te permite tratar eso como un error. Eso es deber del compilador de hacerlo. El mío es de usarlo lo más cómodamente posible. Comprendo que esto está hecho para hacerlo de forma lineal al orden en el que fueron declarados los argumentos de función. Pero ello implica a seguir un orden que no siempre suele ser el más cómodo. Siendo que para solucionarlo debes alterar el orden y provocar que todos sigan el contrato en el está función porque te pasa por no tener un oráculo que todo lo ve y debes haber previsto aún cuando tú código sea humilde.

Conclusión mejor no tocar nada. Bueno no, es que sí que me parece buena idea remplazar los argumentos de una plantilla para puedan ser explícitos. 

¿A qué viene a todo esto hablar de chorrada? Con esto podemos conseguir mayor versatilidad de modificar la tabla lut por karnaugh.

Mi idea es que desde el código sea capaz que la comprobación rd_pc ocupa el mismo espacio y posición dentro de una instrucción y por lo tanto podemos asumir que son la misma variable para hacer una simplificación por karnaugh eficiente. Siendo que de hacerlo así podríamos incurrir en diferenciarlas en dos o más. 

Además otra idea que podríamos plantear es tener una mega estructura con todas las variables ordenadas y conocer ya de un vistazo qué variables hay que mirar (las que están con 1) y las que están a 0 y las que no se exponen por que no influyen (x en karnaugh).

Aquí entra otro punto de vista que puede complicar todo. Y es que al ser esto un lenguaje de algo nivel, lo vamos a tener bien difícil si queremos por ejemplo para algunos campos considerarlos en conjunto o por separado. Por si tenemos que ocupar 3 bits o cada bit en las mismas posiciones ocupadas tiene significado diferente.

Eureka!
Creo que ahora sí. Como siempre el algebra de bool viene a salvarnos. Lo que podemos hacer es una cuestión fácil para salvarnos de la avaricia de usar structs. Estos son grandes y verbosos. Pero con esta idea ya nada será mejor.

La línea final es que utilicemos dos números de 32 bits: uno para indicar true o false y otro para indicar los don't care bits o una máscara de los que sí we care.

De esta forma podemos expresar con la máscara qué bits realmente están activos o desactivos de los ignorables para karnaugh. Además así damos una ventaja muy grande a manipular de datos como quisiere y a expresar el significado de los bits como se les dé la puñetera gana.

Pero Iván y como hacemos esto, pero si parece contradictorio porque ahora tenemos que escribir los bits a mano y no es nada cómodo? Muy buena pregunta, Iván (estoy chalado). Debemos acordarnos de los extractores. Con set_high podemos poner a uno los bits de interés. Y através de los mismos podemos recuperar información de interés y reinterpretar los datos.

Así evitamos pasar múltiples u8 como bool sino que ahora cambia la partida y ahora solo te doy dos números y tu te las apañas. Bueno, aquí tú es nuevamente yo. EL cambio será mínimo, solo hay que declarar arriba del todo las variables con siginificado o alojarlas en el ámbito donde realemente se use con seguridad porque así evitamos al compilador si una variable no se usa en tiempo de compilación por el conjunto de decisiones tomadas para generar la plantilla. Claro ahora así. Por ejemplo podemos tener que una mayor granuaridad al ajustar qué operaciones realizar. Aunque el compilador siga siendo muy listo pero creo que así se damos pilas para volar por bits! Un ejemplo muy claro es en operand2, hay un caso que de 7 variables usa 2 para una rama. Y el resto son descartadas.

¡TODO HA CAMBIADO!

Creo que ahora sí va cobrando más sentido y la sintaxis sería algo talque así:

``` c++


// field.hpp
namespace neogba {

/**
 * @brief Describes a contiguous bit field within an instruction encoding.
 *
 * Provides compile-time utilities to extract and insert a bit or bits field using a mask and shift
 * value.
 *
 * @tparam instruction_t Instruction type. `u32` for ARM. `u16` for Thumb.
 * @tparam return_t Type returned by the extracted field.
 * @tparam n_shift Least significant bit position of the field.
 * @tparam bit_mask Bit mask identifying the field.
 */
template <typename instruction_t, typename return_t, u8 n_shift, instruction_t bit_mask = 0xfu,
          typename alternative_return_t = return_t>
struct field {
  using ins_t = instruction_t;
  using ret_t = return_t;
  using alt_ret_t = alternative_return_t;
  static constexpr u8 shift{n_shift};
  static constexpr ins_t mask{bit_mask};

  /**
   * @brief Extracts the field value from an instruction.
   *
   * @param instruction Raw 32-bit ARM instruction.
   * @return Retrieved value from instruction.
   */
  [[nodiscard]] static inline constexpr ret_t get(ins_t instruction) {

    return static_cast<ret_t>(((instruction) & (mask)) >> shift);
  }
  /**
   * @brief Replaces the field value within an instruction.
   *
   * @param instruction Raw 32-bit ARM instruction.
   * @param value Raw value to set in the field.
   * @return Copy of the instruction and replaced field.
   */
  [[nodiscard]] static inline constexpr ins_t set(ins_t instruction, ret_t value) {
    return ((instruction) & (~mask)) | ((value << shift) & mask);
  }

  [[nodiscard]] static inline constexpr ins_t set(ins_t instruction, alt_ret_t value)
    requires(!std::same_as<alt_ret_t, ret_t>)
  {
    return set(instruction, static_cast<ret_t>(value));
  }

  /**
   * @brief Adds binary ones the field value within an instruction.
   *
   * @param value Raw value to set of the field.
   * @return That original value shifted and masked.
   */
  [[nodiscard]] static inline constexpr ins_t set_high(ret_t value) {
    return (value << shift) & mask;
  }

  [[nodiscard]] static inline constexpr ins_t set_high(alt_ret_t value)
    requires(!std::same_as<alt_ret_t, ret_t>)
  {
    return set_high(static_cast<ret_t>(value));
  }
};

/**
 * @brief Convenient wrapper for fields defined by an unshifted mask.
 *
 * The supplied mask is automatically shifted by `n_shift` before creating the underlying
 * `field`.
 *
 * @tparam instruction_t Instruction type.
 * @tparam return_t Extracted value type.
 * @tparam n_shift Least significant bit position of the field.
 * @tparam base_mask Unshifted field mask.
 * @tparam alternative_return_t Alternative type to avoid writing static_cast.
 *
 * @see field
 */
template <typename instruction_t, typename return_t, u8 n_shift, instruction_t base_mask = 0xfu,
          typename alternative_return_t = return_t>
struct field_delayed
    : field<instruction_t, return_t, n_shift, (base_mask << n_shift), alternative_return_t> {};

/**
 * @brief Specialization for single-bit instruction fields.
 *
 * Provides boolean accessors and convenience operations for manipulating individual bits.
 *
 * @tparam instruction_t Instruction type.
 * @tparam n_shift Bit position.
 *
 * @see field
 */
template <typename instruction_t, u8 n_shift>
struct field_bool : field<instruction_t, bool, n_shift, (1u << n_shift)> {
  using ins_t = instruction_t;

  /**
   * @brief Returns the bit as a boolean value.
   *
   * @param instruction Raw 32-bit ARM instruction.
   * @return Retrieved boolean from instruction.
   */
  [[nodiscard]] static constexpr bool get(ins_t instruction) {
    return ((instruction)&field_bool::mask) != 0;
  }

  /**
   * @brief Returns the bit as a 8 bit unsigned value.
   *
   * @param instruction Raw 32-bit ARM instruction.
   * @return Retrieved bit as 8 bit unsigned from instruction, but masked and shifted.
   */
  [[nodiscard]] static constexpr u8 get_raw(ins_t instruction) {
    return ((instruction)&field_bool::mask) >> n_shift;
  }

  /**
   * @brief Sets or clears the bit given an instruction.
   *
   * @param instruction Raw 32-bit ARM instruction.
   * @param value Sets if `true`, clears if `false`.
   * @return Copy of the instruction with the bit changed.
   */
  [[nodiscard]] static constexpr ins_t set(ins_t instruction, bool value) {
    return ((instruction) & (~field_bool::mask)) | (value ? field_bool::mask : 0);
  }

  /**
   * @brief Clears the bit given an instruction.
   *
   * @param instruction Raw 32-bit ARM instruction.
   * @return Copy of the instruction with bit cleared.
   */
  [[nodiscard]] static constexpr ins_t set0(ins_t instruction) {
    return instruction & ~field_bool::mask;
  }

  /**
   * @brief Sets the bit given an instruction.
   *
   * @param instruction Raw 32-bit ARM instruction.
   * @return Copy of the instruction with bit set.
   */
  [[nodiscard]] static constexpr ins_t set1(ins_t instruction) {
    return instruction | field_bool::mask;
  }

  /**
   * @brief Toggles the bit given an instruction.
   *
   * toggle `true` becomes `false` and viceversa.
   *
   * @param instruction Raw 32-bit ARM instruction.
   * @return Copy of the instruction with bit toggled.
   */
  [[nodiscard]] static constexpr ins_t toggle(ins_t instruction) {
    return instruction ^ field_bool::mask;
  }

  /**
   * @brief Adds binary one in the field value within an instruction.
   *
   * @return That bit shifted and masked.
   */
  [[nodiscard]] static inline constexpr ins_t set_high() { return field_bool::mask; }
};

// Antes 


template <bool i = false, bool p = false, bool u = false, bool b = false, bool w = false,
          bool l = false, bool rd_pc = false>
void arm_singletrans_generator(arm7tdmi& cpu, u32 inst) {
  const auto r_base{ISA_ARM_SINGLETRANS_RN::get(inst)}, src_dst{ISA_ARM_SINGLETRANS_RD::get(inst)};

  u32 offset;
  if constexpr (i) {
    offset = arm_fsr_operand2_lut.invoke(inst, cpu, inst).result;
  } else {
    offset = ISA_ARM_SINGLETRANS_OFFSET::get(inst);
  }
/// ....

// Ahora
template <u32 tflags>
void arm_singletrans_generator(arm7tdmi& cpu, u32 inst) {
  const auto r_base{ISA_ARM_SINGLETRANS_RN::get(inst)}, src_dst{ISA_ARM_SINGLETRANS_RD::get(inst)};

  constexpr u32 i{ISA_ARM_SINGLETRANS_I::get(tflags)} 

  u32 offset;
  if constexpr (i) {
    offset = arm_fsr_operand2_lut.invoke(inst, cpu, inst).result;
  } else {
    offset = ISA_ARM_SINGLETRANS_OFFSET::get(inst);
  }

/// ....


// de forma que podemos ahora instaciar así
lut.put_raw(0, arm_singletrans_generator<ISA_ARM_SINGLETRANS_TEMPLATE | ISA_ARM_SINGLETRANS_OFFSET::set_high()>);
```

Aunque creo que la sintaxis sigue siendo muy larga. Y creo que lo podemos solucionar utilizando namespaces.

Aquí viene otra iteración más, y es que nos la pelan los we care bits dentro de la plantilla. ¿Por qué? porque no somos ni karnaugh ni la lut y asumimos que la que nos llega está bien. Además solo cabe observar Fsr y operand2 que hemos hecho oídos sordos a los x.

Hay un caveat que hay que tener en cuenta y es que ahora podemos generar hasta 2^32 funciones cómo máximo que hagan absolutamente lo mismo, esto es porque si podemos un 1 donde sea ignorado para ese generador de instrucciones resultará en dos punteros función distintos pero con exactamente mismo código que donde tenga ese bit a 0.

Aunque esto no debería ser un problema porque tenemos los extractores que hacen bastante visible y legible donde está el fallo, hay que seguir teniendo en cuenta esto.

Otra idea que podríamos llevar a cabo, aunque haciendo esto directamente nos quitamos el problema de antes pero añadimos creo que más tiempo de compilación. Puede ser revolucionario. Y es...

Hacer un meta-metagenerador! Wow.

En que consiste? Fácil este meta²generador está compuesto de dos fases en una primera fase se encarga de hacer de router e identificar el tipo correcto de instrucción a generar. Y luego delega la tarea de generar la función al generador concreto.

¿Qué conseguimos? que podemos generar siempre funciones correctas pasando de 0..2³² con un range. Suponiendo que su implementación no tiene errores.

meta²generador no hará uso de luts, delegará con ifs y tiempo de compilación la tarea de generar esta forma. ¿Y para qué carajos quiero esto? fácil porque así un for o un range se encarga de llenar la tabla y mientras nos podemos enfocar en hacer el karnaugh correctamente y así confiar plenamente en la matemática para el rellenado y recuperación de bits.

Es más ahora podemos cambiar nuestras prioridades y dedicarnos a hacer el karnaugh bien y despreocuparnos de cambiarlo.

A ver esta idea sobre el papel parece que vaya a salvar Orihuela del software de paupérrima calidad. Y en cierta parte lo es, pero lo que realmente va a acabar haciendo es sustituir parte de los mecanismos de karnaugh. Bueno no te creas... A ver, la idea esta es poner ifs en compilación con constexpr para decidir que función utilizar en el durante el llenado. Y luego en los test lo podríamos llegar a utilizar como para decir dame el puntero de función correcto de este churro. Claro y podemos conseguir una garantía de que lo que se genere de ahí ya sea único.

Para esto yo creo que deberíamos tener variables extras para los campos como:

``` c++

/// Halfword data transfer, register offset
constexpr u32 ISA_ARM_HALFREG_TEMPLATE{0x00000090u};
constexpr u32 ISA_ARM_HALFREG_FIXED{0x...u}; // NUEVO! es una máscara los con bits son fijos en template (esto es 0 1 que deben estar en esa posición porque si no están ahí está mal)
constexpr u32 ISA_ARM_HALFREG_CARE{0x...u}; // NUEVO! es una máscara los con bits que son utilizados para el tiempo de compilación. Por ejemplo el bit rd sí por que podemos conocer si es pc o no. Pero no importa si es bit4 en singletrans.
using ISA_ARM_HALFREG_P = /*               */ field_bool<u32, 24>;
using ISA_ARM_HALFREG_U = /*               */ field_bool<u32, 23>;
using ISA_ARM_HALFREG_W = /*               */ ISA_ARM_MULTIPLY_A;
using ISA_ARM_HALFREG_L = /*               */ ISA_ARM_FSR_S;
using ISA_ARM_HALFREG_RN = /*              */ ISA_ARM_FSR_RN;
using ISA_ARM_HALFREG_RD = /*              */ ISA_ARM_FSR_RD;
using ISA_ARM_HALFREG_S = /*               */ field_bool<u32, 6>;
using ISA_ARM_HALFREG_H = /*               */ field_bool<u32, 5>;
using ISA_ARM_HALFREG_RM = /*              */ ISA_ARM_MULTIPLY_RM;

```

Creo que delegar un for de 32 GB a compilar no creo que sea tan buena idea. No obstante lo que podemos hacer es de todo ese rango, podemos podar cual algoritmo. Es decir, la idea aquí en lugar de un range logo sería solo coger un conjunto de instrucciones límite e iterar sobre estas. Por ejemplo, así podemos cubrir todo eficientemente y saber con certeza y desde un pov del tester, solo observando casos condiciones. Pero además esto nos puede servir como anillo al dedo a conocer nuestro orden en el karnaugh fácilmente.

Me explico: 

``` c++
{
 using namespace ...;
 for (auto i : {TEMPLATE | P | RD_PC}) // llenar
}

{
 using namespace ...2;
 for (auto i : {TEMPLATE | I | B}) // llenar
}
```

Y además tal y como se muestra podríamos organizarlo por categorías! o en lugar de usar un for usar un sequence y que ya por debajo por la enumeración con algún offset y máscara podamos sincronizar karnaugh con lo esencial.

Bueno un for no podemos utilizar en con plantillas sino que nos vemos forzados a utilizar index_sequence.

Con esto acabamos de salvar la ram de todas computadoras.

Lo próximo que pueda hacer es que hemos practicado la reducción por karnaugh que considero necesario hacer una búsqueda exahustiva cómo está puesta la simplificación. Para hacerlo todo más fácil.

vale. mgba reserva una tabla de 1 << 12 espacios.

``` c
// mgba/src/arm/decoder-arm.c
static const ARMDecoder _armDecoderTable[0x1000] = {
	DECLARE_ARM_EMITTER_BLOCK(_ARMDecode)
};

void ARMDecodeARM(uint32_t opcode, struct ARMInstructionInfo* info) {
	memset(info, 0, sizeof(*info));
	info->execMode = MODE_ARM;
	info->opcode = opcode;
	info->branchType = ARM_BRANCH_NONE;
	info->condition = opcode >> 28;
	info->sInstructionCycles = 1;
	ARMDecoder decoder = _armDecoderTable[((opcode >> 16) & 0xFF0) | ((opcode >> 4) & 0x00F)];
	decoder(opcode, info);
}
```

También por lo que he visto es que ARM hace muchas perradas y no utiliza un karnaugh purista y es como que necesario hacerlo en un orden y sobre escribiendo anteriores. No sé con total exactitud, pero lo que sé es que nuestros han tomado un approach más simple y directo. solo con 12 bits.

Para nuestra implementación deberíamos coger también el rd (0xf << 12). Ojo una cosa muy nueva es que podemos reducir y alterar. De hecho, mirando de pasada y creo que podemos hacerlo que sea de 12 bits y aplicarle más optimizaciones.

Te explico porque fácilmente.

tenemos en bytes una instucción típica así.


``` text
COND | numeros fijos | opcode | campo1 | campo 2 | campo3 | campo4 | campo5
```

aprox, y groso modo.
numeros fijos y opcode sí están contemplados en el mgba.

Ahora bien en el mgba contemplan del bit 4 al 7. Lo cual está ok si realmente llegan a utilizar el bit4 del operand2 como una estrategia para acceder a la operación de operand2 directamente. Vale no.
Imposible! Está bien.

Porque hay un tipo de instrucción que sí lo requiere para ser idenficado.
Mi plan ahora ver si puedo reemplazar el bit 7 para expresar la variable rd_pc == 0xf

mentira el bit7 en la de alu fsr, el bit7 es tratado por otra función que es llamada por dentro de la función de instrucción concreta. Además por parámetro siempre tiene la instucción exacta por lo que a las malas a t.ejecución como bien hacen mgba!


```
vale pesemos un paso más allá.

mgba utiliza algo como esto para el propósito de optimizar los accesos correspondientes a cad



vale. mgba reserva una tabla de 1 << 12 espacios.

```c
// mgba/src/arm/decoder-arm.c
static const ARMDecoder _armDecoderTable[0x1000] = {
    DECLARE_ARM_EMITTER_BLOCK(_ARMDecode)
};

void ARMDecodeARM(uint32_t opcode, struct ARMInstructionInfo* info) {
    memset(info, 0, sizeof(*info));
    info->execMode = MODE_ARM;
    info->opcode = opcode;
    info->branchType = ARM_BRANCH_NONE;
    info->condition = opcode >> 28;
    info->sInstructionCycles = 1;
    ARMDecoder decoder = _armDecoderTable[((opcode >> 16) & 0xFF0) | ((opcode >> 4) & 0x00F)];
    decoder(opcode, info);
}
```



mi pregunta es consideras que: podamos remplazar alguna parte de la máscara para que contenga la información rd\_pc (read 0xf << 12) == 15 que queda más o menos en los mismos sitios que en todas las instrucciones reduciendo a un bit?



Considera la información de la imagen!

Considera el siguiente código



```
#pragma once
#include "neogba/arm7tdmi/isa/arm_mode/operand2.hpp"
#include <utility>

namespace neogba {
/**
 * @brief Executes a compile-time specialized ARM data-processing instruction.
 *
 * This template generates the implementation of an ARM Flexible Second Operand (FSR)
 * data-processing instruction. The selected opcode and execution behaviour could be entirely
 * resolved at compile time using template parameters, allowing the compiler to remove unused
 * branches and optimize the generated code for each instruction variant.
 *
 * Depending on the template arguments, the generated implementation may update the CPSR flags,
 * write the result to the program counter, or implement flag-only instructions such as CMP or
 * TST.
 *
 * @tparam opcode Data-processing opcode to execute.
 * @tparam s Whether the instruction updates the CPSR condition flags.
 * @tparam rd_pc Whether the destination register is R15 (PC).
 *
 * @param cpu ARM7TDMI CPU state to execute the instruction on.
 * @param inst Raw 32-bit ARM instruction.
 *
 * @note All instruction-specific decisions are resolved at compile time using `if constexpr`, so
 * the generated machine code contains only the logic required for the selected instruction
 * variant with least branches at execution-time.
 *
 * @warning Setting `rd_pc` when `opcode` is one of (`TST`, `TEQ`, `CMP`, `CMN`) is not a
 * documented behaviour in ARM. Because these opcodes only write side effects (by updating CPSR)
 * and ignore destination `rd` field. According, it is illegal to write that on assembly (`rd`
 * contains trash).
 *
 * @warning If the instruction `opcode` is one of (`TST`, `TEQ`, `CMP`, `CMN`), then the flag S is
 * implicitly set. If else, it means it's another instruction type. This fucntion is not
 * responsible for handling that!
 *
 * @todo Testing this function.
 * @todo Ensure correct handling when r15 is involved as source or as destination.
 *
 * @see arm_operand2_generator
 * @see arm_operand2_lut
 * @see arm_fsr_opcode
 * @see arm7tdmi
 */
template <arm_fsr_opcode opcode, bool s = false, bool rd_pc = false>
void arm_fsr_generator(arm7tdmi& cpu, u32 inst) {
  // Meta template variables
  constexpr auto is_logical{opcode == arm_fsr_opcode::AND || opcode == arm_fsr_opcode::EOR ||
                            opcode == arm_fsr_opcode::TST || opcode == arm_fsr_opcode::TEQ ||
                            opcode == arm_fsr_opcode::ORR || opcode == arm_fsr_opcode::MOV ||
                            opcode == arm_fsr_opcode::BIC || opcode == arm_fsr_opcode::MVN};
  constexpr auto can_write_rd{!(opcode == arm_fsr_opcode::TST || opcode == arm_fsr_opcode::TEQ ||
                                opcode == arm_fsr_opcode::CMP || opcode == arm_fsr_opcode::CMN)};
  constexpr auto is_inverted_sub{opcode == arm_fsr_opcode::RSB || opcode == arm_fsr_opcode::RSC};
  constexpr auto is_not_move{opcode != arm_fsr_opcode::MOV && opcode != arm_fsr_opcode::MVN};
  constexpr auto is_sum{opcode == arm_fsr_opcode::ADD or opcode == arm_fsr_opcode::ADC or
                        opcode == arm_fsr_opcode::CMN};

  // Retrieve values
  u8 rd_idx;
  u32 op1;
  u64 res;
  auto rn_idx{ISA_ARM_FSR_RN::get(inst)};

  if constexpr (rd_pc)
    rd_idx = 0xfu;
  else
    rd_idx = ISA_ARM_FSR_RD::get(inst);

  if constexpr (is_not_move)
    op1 = cpu.read_active_register(rn_idx);

  auto op2{arm_fsr_operand2_lut.invoke(inst, cpu, inst)};

  if constexpr (is_inverted_sub)
    std::swap(op1, op2.result);

  // Perform operation
  if constexpr (opcode == arm_fsr_opcode::AND || opcode == arm_fsr_opcode::TST)
    res = op1 & op2.result;
  else if constexpr (opcode == arm_fsr_opcode::EOR || opcode == arm_fsr_opcode::TEQ)
    res = op1 ^ op2.result;
  else if constexpr (opcode == arm_fsr_opcode::SUB || opcode == arm_fsr_opcode::CMP ||
                     opcode == arm_fsr_opcode::RSB)
    res = static_cast<u64>(op1) - op2.result;
  else if constexpr (opcode == arm_fsr_opcode::ADD || opcode == arm_fsr_opcode::CMN)
    res = static_cast<u64>(op1) + op2.result;
  else if constexpr (opcode == arm_fsr_opcode::ADC)
    res = static_cast<u64>(op1) + op2.result + op2.carry_in;
  else if constexpr (opcode == arm_fsr_opcode::SBC || opcode == arm_fsr_opcode::RSC)
    res = static_cast<u64>(op1) - op2.result + op2.carry_in - 1;
  else if constexpr (opcode == arm_fsr_opcode::ORR)
    res = op1 | op2.result;
  else if constexpr (opcode == arm_fsr_opcode::MOV)
    res = op2.result;
  else if constexpr (opcode == arm_fsr_opcode::BIC)
    res = op1 & ~op2.result;
  else if constexpr (opcode == arm_fsr_opcode::MVN)
    res = ~op2.result;

  // write back the result
  auto res32{static_cast<u32>(res)};
  if constexpr (can_write_rd)
    cpu.write_active_register(rd_idx, res32);

  // Side effects
  if constexpr (s) {
    if constexpr (rd_pc and can_write_rd) {
      cpu.write_cpsr(cpu.read_spsr());

    } else {

      // common
      auto z{static_cast<u32>(res32 == 0) << arm7tdmi::Z_SHIFT}; // (res32 == 0) -> true -> 0x0...01
      u32 n{res32 & 0x80000000}; // N ya está en el bit 31 -> 0 movimientos

      if constexpr (is_logical) {
        auto c{static_cast<u32>(op2.carry_out << arm7tdmi::C_SHIFT)}; // op2.carry_out es 0 o 1.

        // meter V aquí = !necesario -> no está afectado.
        // set_cpsr(mask, values) sobrescribe solo estos `mask`
        cpu.set_cpsr(arm7tdmi::Z | arm7tdmi::N | arm7tdmi::C, z | n | c);
      } else {
        auto c{static_cast<u32>(res >> 32)}; // (res >> 32) & 1 es 1 o 0.
        auto v{~(op1 ^ op2.result)};

        if constexpr (not is_sum) {
          c = !c;
          v = ~v;
        }

        c = (c & 1) << arm7tdmi::C_SHIFT; // Mover lo necesario!
        v = (v & (op1 ^ res32) & 0x80000000) >>
            (31 - arm7tdmi::V_SHIFT); // Mover lo justo al bit V.

        cpu.set_cpsr(arm7tdmi::Z | arm7tdmi::N | arm7tdmi::C | arm7tdmi::V, z | n | c | v);
      }
    }
  }
}

inline constexpr auto

    arm_fsr_AND_notS_notRdPC{arm_fsr_generator<arm_fsr_opcode::AND>},
    arm_fsr_EOR_notS_notRdPC{arm_fsr_generator<arm_fsr_opcode::EOR>},
    arm_fsr_SUB_notS_notRdPC{arm_fsr_generator<arm_fsr_opcode::SUB>},
    arm_fsr_RSB_notS_notRdPC{arm_fsr_generator<arm_fsr_opcode::RSB>},
    arm_fsr_ADD_notS_notRdPC{arm_fsr_generator<arm_fsr_opcode::ADD>},
    arm_fsr_ADC_notS_notRdPC{arm_fsr_generator<arm_fsr_opcode::ADC>},
    arm_fsr_SBC_notS_notRdPC{arm_fsr_generator<arm_fsr_opcode::SBC>},
    arm_fsr_RSC_notS_notRdPC{arm_fsr_generator<arm_fsr_opcode::RSC>},
    arm_fsr_ORR_notS_notRdPC{arm_fsr_generator<arm_fsr_opcode::ORR>},
    arm_fsr_MOV_notS_notRdPC{arm_fsr_generator<arm_fsr_opcode::MOV>},
    arm_fsr_BIC_notS_notRdPC{arm_fsr_generator<arm_fsr_opcode::BIC>},
    arm_fsr_MVN_notS_notRdPC{arm_fsr_generator<arm_fsr_opcode::MVN>},
    arm_fsr_AND_S_notRdPC{arm_fsr_generator<arm_fsr_opcode::AND, true>},
    arm_fsr_EOR_S_notRdPC{arm_fsr_generator<arm_fsr_opcode::EOR, true>},
    arm_fsr_SUB_S_notRdPC{arm_fsr_generator<arm_fsr_opcode::SUB, true>},
    arm_fsr_RSB_S_notRdPC{arm_fsr_generator<arm_fsr_opcode::RSB, true>},
    arm_fsr_ADD_S_notRdPC{arm_fsr_generator<arm_fsr_opcode::ADD, true>},
    arm_fsr_ADC_S_notRdPC{arm_fsr_generator<arm_fsr_opcode::ADC, true>},
    arm_fsr_SBC_S_notRdPC{arm_fsr_generator<arm_fsr_opcode::SBC, true>},
    arm_fsr_RSC_S_notRdPC{arm_fsr_generator<arm_fsr_opcode::RSC, true>},
    arm_fsr_ORR_S_notRdPC{arm_fsr_generator<arm_fsr_opcode::ORR, true>},
    arm_fsr_MOV_S_notRdPC{arm_fsr_generator<arm_fsr_opcode::MOV, true>},
    arm_fsr_BIC_S_notRdPC{arm_fsr_generator<arm_fsr_opcode::BIC, true>},
    arm_fsr_MVN_S_notRdPC{arm_fsr_generator<arm_fsr_opcode::MVN, true>},
    arm_fsr_AND_S_RdPC{arm_fsr_generator<arm_fsr_opcode::AND, true, true>},
    arm_fsr_EOR_S_RdPC{arm_fsr_generator<arm_fsr_opcode::EOR, true, true>},
    arm_fsr_SUB_S_RdPC{arm_fsr_generator<arm_fsr_opcode::SUB, true, true>},
    arm_fsr_RSB_S_RdPC{arm_fsr_generator<arm_fsr_opcode::RSB, true, true>},
    arm_fsr_ADD_S_RdPC{arm_fsr_generator<arm_fsr_opcode::ADD, true, true>},
    arm_fsr_ADC_S_RdPC{arm_fsr_generator<arm_fsr_opcode::ADC, true, true>},
    arm_fsr_SBC_S_RdPC{arm_fsr_generator<arm_fsr_opcode::SBC, true, true>},
    arm_fsr_RSC_S_RdPC{arm_fsr_generator<arm_fsr_opcode::RSC, true, true>},
    arm_fsr_ORR_S_RdPC{arm_fsr_generator<arm_fsr_opcode::ORR, true, true>},
    arm_fsr_MOV_S_RdPC{arm_fsr_generator<arm_fsr_opcode::MOV, true, true>},
    arm_fsr_BIC_S_RdPC{arm_fsr_generator<arm_fsr_opcode::BIC, true, true>},
    arm_fsr_MVN_S_RdPC{arm_fsr_generator<arm_fsr_opcode::MVN, true, true>},
    arm_fsr_AND_notS_RdPC{arm_fsr_generator<arm_fsr_opcode::AND, false, true>},
    arm_fsr_EOR_notS_RdPC{arm_fsr_generator<arm_fsr_opcode::EOR, false, true>},
    arm_fsr_SUB_notS_RdPC{arm_fsr_generator<arm_fsr_opcode::SUB, false, true>},
    arm_fsr_RSB_notS_RdPC{arm_fsr_generator<arm_fsr_opcode::RSB, false, true>},
    arm_fsr_ADD_notS_RdPC{arm_fsr_generator<arm_fsr_opcode::ADD, false, true>},
    arm_fsr_ADC_notS_RdPC{arm_fsr_generator<arm_fsr_opcode::ADC, false, true>},
    arm_fsr_SBC_notS_RdPC{arm_fsr_generator<arm_fsr_opcode::SBC, false, true>},
    arm_fsr_RSC_notS_RdPC{arm_fsr_generator<arm_fsr_opcode::RSC, false, true>},
    arm_fsr_ORR_notS_RdPC{arm_fsr_generator<arm_fsr_opcode::ORR, false, true>},
    arm_fsr_MOV_notS_RdPC{arm_fsr_generator<arm_fsr_opcode::MOV, false, true>},
    arm_fsr_BIC_notS_RdPC{arm_fsr_generator<arm_fsr_opcode::BIC, false, true>},
    arm_fsr_MVN_notS_RdPC{arm_fsr_generator<arm_fsr_opcode::MVN, false, true>},
    arm_fsr_TST_notRdPC{arm_fsr_generator<arm_fsr_opcode::TST, true>},
    arm_fsr_TEQ_notRdPC{arm_fsr_generator<arm_fsr_opcode::TEQ, true>},
    arm_fsr_CMP_notRdPC{arm_fsr_generator<arm_fsr_opcode::CMP, true>},
    arm_fsr_CMN_notRdPC{arm_fsr_generator<arm_fsr_opcode::CMN, true>},
    arm_fsr_TST_RdPC{arm_fsr_generator<arm_fsr_opcode::TST, true, true>},
    arm_fsr_TEQ_RdPC{arm_fsr_generator<arm_fsr_opcode::TEQ, true, true>},
    arm_fsr_CMP_RdPC{arm_fsr_generator<arm_fsr_opcode::CMP, true, true>},
    arm_fsr_CMN_RdPC{arm_fsr_generator<arm_fsr_opcode::CMN, true, true>};
} // namespace neogba

```

Considera que operand2 es externo por cuestiones de diseño para facilitar su reutilización y por lo tanto como puedes apreciar en el código, es una llamada externa que bien hace todo el cómputo necesario.

Considera que seguir a raja tabla la tabla de decodiciación de arm como mínima garantía de la verdad 

  ``` text
  |..3 ..................2 ..................1 ..................0|
  |1_0_9_8_7_6_5_4_3_2_1_0_9_8_7_6_5_4_3_2_1_0_9_8_7_6_5_4_3_2_1_0|
  |_Cond__|0_0_0|___Op__|S|__Rn___|__Rd___|__Shift__|Typ|0|__Rm___| DataProc
  |_Cond__|0_0_0|___Op__|S|__Rn___|__Rd___|__Rs___|0|Typ|1|__Rm___| DataProc
  |_Cond__|0_0_1|___Op__|S|__Rn___|__Rd___|_Shift_|___Immediate___| DataProc
  |_Cond__|0_0_1_1_0_0_1_0_0_0_0_0_1_1_1_1_0_0_0_0|_____Hint______| ARM11:Hint
  |_Cond__|0_0_1_1_0|P|1|0|_Field_|__Rd___|_Shift_|___Immediate___| PSR Imm
  |_Cond__|0_0_0_1_0|P|L|0|_Field_|__Rd___|0_0_0_0|0_0_0_0|__Rm___| PSR Reg
  |_Cond__|0_0_0_1_0_0_1_0_1_1_1_1_1_1_1_1_1_1_1_1|0_0|L|1|__Rn___| BX,BLX
  |1_1_1_0|0_0_0_1_0_0_1_0|_____immediate_________|0_1_1_1|_immed_| ARM9:BKPT
  |_Cond__|0_0_0_1_0_1_1_0_1_1_1_1|__Rd___|1_1_1_1|0_0_0_1|__Rm___| ARM9:CLZ
  |_Cond__|0_0_0_1_0|Op_|0|__Rn___|__Rd___|0_0_0_0|0_1_0_1|__Rm___| ARM9:QALU
  |_Cond__|0_0_0_0_0_0|A|S|__Rd___|__Rn___|__Rs___|1_0_0_1|__Rm___| Multiply
  |_Cond__|0_0_0_0_0_1_0_0|_RdHi__|_RdLo__|__Rs___|1_0_0_1|__Rm___| ARM11:UMAAL
  |_Cond__|0_0_0_0_1|U|A|S|_RdHi__|_RdLo__|__Rs___|1_0_0_1|__Rm___| MulLong
  |_Cond__|0_0_0_1_0|Op_|0|Rd/RdHi|Rn/RdLo|__Rs___|1|y|x|0|__Rm___| MulHalfARM9
  |_Cond__|0_0_0_1_0|B|0_0|__Rn___|__Rd___|0_0_0_0|1_0_0_1|__Rm___| TransSwp12
  |_Cond__|0_0_0_1_1|_Op__|__Rn___|__Rd___|1_1_1_1|1_0_0_1|__Rm___| ARM11:LDREX
  |_Cond__|0_0_0|P|U|0|W|L|__Rn___|__Rd___|0_0_0_0|1|S|H|1|__Rm___| TransReg10
  |_Cond__|0_0_0|P|U|1|W|L|__Rn___|__Rd___|OffsetH|1|S|H|1|OffsetL| TransImm10
  |_Cond__|0_1_0|P|U|B|W|L|__Rn___|__Rd___|_________Offset________| TransImm9
  |_Cond__|0_1_1|P|U|B|W|L|__Rn___|__Rd___|__Shift__|Typ|0|__Rm___| TransReg9
  |_Cond__|0_1_1|________________xxx____________________|1|__xxx__| Undefined
  |_Cond__|0_1_1|Op_|x_x_x_x_x_x_x_x_x_x_x_x_x_x_x_x_x_x|1|x_x_x_x| ARM11:Media
  |1_1_1_1_0_1_0_1_0_1_1_1_1_1_1_1_1_1_1_1_0_0_0_0_0_0_0_1_1_1_1_1| ARM11:CLREX
  |_Cond__|1_0_0|P|U|S|W|L|__Rn___|__________Register_List________| BlockTrans
  |_Cond__|1_0_1|L|___________________Offset______________________| B,BL,BLX
  |_Cond__|1_1_0|P|U|N|W|L|__Rn___|__CRd__|__CP#__|____Offset_____| CoDataTrans
  |_Cond__|1_1_0_0_0_1_0|L|__Rn___|__Rd___|__CP#__|_CPopc_|__CRm__| CoRR ARM9
  |_Cond__|1_1_1_0|_CPopc_|__CRn__|__CRd__|__CP#__|_CP__|0|__CRm__| CoDataOp
  |_Cond__|1_1_1_0|CPopc|L|__CRn__|__Rd___|__CP#__|_CP__|1|__CRm__| CoRegTrans
  |_Cond__|1_1_1_1|_____________Ignored_by_Processor______________| SWI
  ```

Considera únicamente las instrucciones lanzables desde el chip ARM7TDMI-s que implementa la arquitectura ARMv4T

La IA es aveces muy cabezona con no ver errores o sí con matices pero el matiz es algo que importa en absoluto. Ninguna ha dado en el motivo exacto.

Vale no es posible remplazar bit7 porque no había formula de identificar bx, bit4 con las coproc, ni tampoco bits superiores por que están demasiado atados. Y todo ello para remplazar por rd_pc==15 no vale la pena. 

Ni aún así con u32 como parámetro porque en realidad eso no influye en nada, eso es recuperar datos de ahí pero si rd_pc es realmente 15 o debería haber preasumido. Y como no podríamos insertar esa info en la lut al momento, esto puede hacer asunciones peligrosamente erróneas. Así como escribir siempre en el pc que se haga una suma, o que el efecto secundario no sea el esperado si el destino es 15.

Podríamos llegar a expandir a 13 bits y fin del problema. Pero no quiero. Sería interesante poder comparar el rendimiento de caché en este caso. No juzgo, solo admiro como de simple es el acercamiento al problema de mgba. Denota sus años de experiencia.

Rondando por mi cabeza es una idea muy descabellada y que quizás sea hasta controversial. Pero tengo la idea de remplazar el bit 7 por eso de rd_pc. Y cuando sea, `|_Cond__|0_0_0_1_0_0_1_0_1_1_1_1_1_1_1_1_1_1_1_1|0_0|L|1|__Rn___|` exactamente eso ignorando campos variables, hacer una hiper especialización y considerarlo en la lut como una undefined especial.

Pero he ahí el quid de la cuestión. Y es que se algún modo entramos en una paradoja en la que queriendo mejorar el rendimiento lo acabamos de empeorar introduciendo una posible ramificación por cada vez que utilice el normalizador de la lut. Ello o que si ubiese algún operador mágico que coga la instrucción detecte que es esa y sume el offset para ser una del tipo indefinido.

Otra opción sería tratar bx como una multiply pero ahí se queda la idea porque el precómputo de la platilla es fijo a lo largo de toda la vida del programa. Y sería imposible mandar algo por ahí para idenficar bx desde multiply. Esto nace como un error conceptual cómo funciona de metaprogramación. Y es que sigue aquí la regla de oklam (navaja) que todo es por un motivo más simple de lo que realmente parece.

En conclusión, no hay forma de mejorar esto que no sea añadiendo más bits.
Vamos a seguir con los 12 de mgba pero una pequeña peculiaridad y es que vamos cambiar el código lo mínimo posible esto para evitar cambiar mucho para hacer comparativas de rendimiento. Sí realmente marca la diferencia, quizás en un futuro podríamos considerar expandir a 13 bits.

Hoy ha sido un día de completa lucidez! Siento que he avanzado mucho y ahora tengo camino donde seguir bien.

Dicho esto:
- Implementar el "karnaugh" definitivo en la lut general.
- Reemplazar constantes del isa por algo más súper pachamamesco.
- Reemplazar tparams por un único número u32.

# 12 de agosto

Hoy es tu día, https://www.eclipse.org/downloads/ hoy vas a renacer aunque no en forma de Java IDE.

Vamos a empezar con los ISA constants

# 13 de agosto

Mierda de operator() no funciona. Pero bueno mejor, así tengo que mantener menos cosas. Y he simplificado bastante la sintaxis.
Voy a añadir la máscara de fixed a cada tipo de instrucción.

Otra cosa que considero necesaria ir comprobando es implementar al proyecto compilación progresiva por tema de ir reduciendo los tiempos de compilación. Y que solo se recompile las partes necesarias.

Hubo una vez que cogí el proyecto de lineage os para compilarlo para un móvil no compatible, tardé un mes. Pero la cosa es que la compilación fallaba en mitad. Con lo que tenía que volver a arrancar el proceso. Sin embargo hacer esto, no hacía que fuera a empezar desde 0 sino que continuaba por donde se había quedado. Y a base de insistir conseguir compilar el proyecto.

Hecho. Al principio tarda igual que si no fuera nada progresivo. 

Pero en futuras ejecuciones de make, ahora tarda 0, o la mitad si se modifican las cabeceras.

Aquí entramos en un dilema y es que para reducir tiempos de compilación debemos no engrasar tanto los headers. Pero ello es una cuestión imposible si contamos con templates y constantes. Claro está que podemos ahorrarnos la conveniencia de escribir en línea.

Vale un par de cositas.

Ya veo la perrada de arm. Genera confusión el undefined con single data trans. Ahí claramente hay algo raro o alguna excepción de no usar. Otra cuestión que me gustaría tratar es que voy a retratarme de usar `template<u32>`. No voy a hacerlo. Porque eso implicaría generar el meta²generador. Nuestro problema era la legibilidad. Y cosa la cual la podríamos mejorar usando una sintaxis más explícita. Al más puro estilo de Java y Javascript con objetos. Y es que en lugar de usar `template<bool, bool, bool...>` vamos a usar structs que definan una semántica para argumentos. Pero claro c++ exige un orden. Esto es válido para C++20 y se conoce como NNTP.

Vamos a hacer una prueba de concepto, modificando la que teníamos.

``` c++
// ANTES
#include "neogba/structs/lut.hpp"
#include <gtest/gtest.h>

using namespace neogba;

template <bool a = false, bool b = false, bool c = false, bool d = false>
bool superplant(int codigo) {
  return (a << 3 | b << 2 | c << 1 | d) == codigo;
}
using function_type = bool (*)(int);
using lut_type = lut<function_type, 16>;

template <std::size_t I> constexpr function_type expected_function() {
  static_assert(I < 16);

  return &superplant<(I & 0b1000) != 0, (I & 0b0100) != 0, (I & 0b0010) != 0, (I & 0b0001) != 0>;
}

template <std::size_t... I> constexpr lut_type make_lut(std::index_sequence<I...>) {
  lut_type result;

  (result.fill(I, 0, expected_function<I>()), ...);

  return result;
}

TEST(proof_of_concept, template_functions_check_if_runs_match_adhoc) {
  auto mylut{make_lut(std::make_index_sequence<16>())};

  EXPECT_EQ(true, mylut.invoke(8, 8));
  EXPECT_EQ(false, mylut.invoke(8, 9));
  EXPECT_NE(mylut.get(11), mylut.get(10));
  EXPECT_EQ(superplant<true>, mylut.get(8));
  EXPECT_EQ(superplant<true>, superplant<true>);

  //  std::println("s<true>: {:x}\nmylut@8: {:x}",
  //  reinterpret_cast<std::uintptr_t>(&superplant<true>),
  //  reinterpret_cast<std::uintptr_t>(mylut.get(8)));
}


// DESPUÉS

#include "neogba/structs/lut.hpp"
#include <gtest/gtest.h>

using namespace neogba;

struct supertemplate_flags {
  bool a : 1 {false};
  bool b : 1 {false};
  bool c : 1 {false};
  bool d : 1 {false};
  bool experiment : 1 {false};
};

template <supertemplate_flags tflags> bool superplant(int codigo) {
  if constexpr (tflags.experiment)
    return false;
  else
    return (tflags.a << 3 | tflags.b << 2 | tflags.c << 1 | tflags.d) == codigo;
}
using function_type = bool (*)(int);
using lut_type = lut<function_type, 16>;

template <std::size_t I> constexpr function_type expected_function() {
  static_assert(I < 16);

  return &superplant<supertemplate_flags{.a = (I & 0b1000) != 0,
                                         .b = (I & 0b0100) != 0,
                                         .c = (I & 0b0010) != 0,
                                         .d = (I & 0b0001) != 0}>;
}

template <std::size_t... I> constexpr lut_type make_lut(std::index_sequence<I...>) {
  lut_type result;

  (result.fill(I, 0, expected_function<I>()), ...);

  return result;
}

TEST(proof_of_concept, template_functions_check_if_runs_match_adhoc) {
  auto mylut{make_lut(std::make_index_sequence<16>())};

  EXPECT_EQ(true, mylut.invoke(8, 8));
  EXPECT_EQ(false, mylut.invoke(8, 9));
  EXPECT_NE(mylut.get(11), mylut.get(10));
  EXPECT_EQ(superplant<{true}>, mylut.get(8));
  EXPECT_EQ(superplant<supertemplate_flags{.a = true}>, superplant<{.a = true}>);
  EXPECT_EQ(superplant<supertemplate_flags{true}>, superplant<{.a = true}>);
  EXPECT_EQ((superplant<{true}>), (superplant<{.a = true, .b = false}>));
  EXPECT_EQ((superplant<{.a = true}>), (superplant<{.a = true, .b = false}>));
}

```

esta sintaxis hace que la verbosidad pueda ser usada a conveniencia. 

Sin embargo clangd sufre a estragos por las macros de google test. Fuera de esto, va genial. Procedamos a cambiar los parámetros de plantilla por esto de aquí.

He tomado la decisión de mandar a tomar viento el experimento de rd_pc. mgba no lo hace y es el mejor. ya está bien!

Como me he cargado las 300 funciones de fsr vamos a aprovechar para implementar los 12 bits de identificación para la tabla de operaciones del modo arm ya definitiva (TM). 

Creo que conocer el fixed no es nada útil. Pero bueno, ya que está hecho no voy a tocarlo.

Lo último que voy a hacer para hoy es crear una función de undefined. Pero voy a pasar un poco del culo de arm y esta función undefined será la que se rellene. Así podemos ver quizás más claro si hay algo mal rellenado. Que sirva a modo de stub.

Otra cuestión que miraré serán los logs pero esto para el futuro. Pero debería ir poniendo ya.

Por último, debido a estos cambios vamos a hacer que la comprobación de si debe ejecutarse o no (campo cond) la vamos a realizar dentro de la operación. De este modo, podemos dar libertad a ignorar deliberadamente o considerar este campo antes o después de alguna sentencia que fuese necesario en ese preciso momento. O bien para una optimización más loca que si ya desde la lut conocemos que hay puestos el ALWAYS pues podríamos omitir preguntar condicionalmente la ejecución. Esto claro está que requiere introducir almenos un bit en la codificación del normalizador de la tabla lut del modo arm. La condición ALWAYS Permite esto por se temprana de reconocimiento. Al igual que NEVER. Puesto que el resto de condiciones implicar conocer el estado en ese momento de la CPU. Mientras que para las dos mencionadas no están sujetas a estas condiciones en tiempo de ejecución, y podríamos considerarlos como casos incondicionales. Esta bajo mi punto de vista, es algo que si es plausible de identificar y sencillo de realizar. No obstante, aplicar esto quizás podría resultar en execiso uso de la memoria y desembocar en funciones muy similares entre sí. Identificar tempranamente esto nos proporciona la ayuda de ejecutar o no con seguridad una función. El problema es que por cada función se nos genararían dos variantes en caso de always. Cuestión que no es del todo un problema, pero es más memoria. Una variante sería la de always y la de no saber si es always. Pero nos ahorra una llamada. Ahora bien, para el caso de never es interesante considerarlo porque podríamos redirigir las llamadas al vacío y no hacer nada. Siendo que tenemos dos variantes de la misma función una la normal y otra la tonta. También nos ahorra una llamada. Esta no obstante es más fácil de implementar pero sigue requeriendo el doble. La implementación de esta forma sería detectar never y rellenar la tabla con el resto de la máscara. Sin embargo, he mentido que sea el doble, bueno en la tabla sí, pero la función es solo una. De hecho podemos reutilizar la de Undefined para simular el pedazo de NOP. De momento la más favorable para mi parecer es la de implementar never. Pero aquí entraría otra cuestión a considerar y es ¿vale la pena? La verdad es que convendría realizar un estudio más en profundidad sobre el uso que tiene arm7tdmi7 y el impacto en la cache de nuestro computador. Aunque podemos acotar el campo y analizar como se utilizan estos campos en la gba. Bien es cierto es es never antes la cpu no pasa ni por la lut. El tradeoff de hacer esta movida de delegar el cond a sus implementaciones concretas de instrucciones pueda parecer bueno lo cierto es que tiene una ligera penalización: obliga a ejecutar la lut (suponiendo todo el overhead y todo lo que ello conlleva: supongamos que el lambda sí hace inline y solo resulta en solo hay una llamada) + luego comprobar si hay mala suerte de no ser always o never pues preguntar a la cpu sobre su estado (otra llamada) pero si dice que no es posible, entonces la llamada de lut ha sido de más. Pero sí hay éxito, no hemos conseguido ningún beneficio notorio. En cualquiera de los dos casos no especiales nos hemos comido con patacas dos llamadas y en una es perjudicial. Por lo tanto, la pregunga que me hago, debería considerar en implementar esta mejora?, los programas de gba abusan del campo cond? hay algún estudio que avale esto?

Mejor no implementar esto... No vamos a delegar esto. mgba no lo hace y será por algo. Pero es interesante tener en cuenta esto.

https://en.cppreference.com/cpp/language/template_parameters parametros NNTP

Mejor hago undefined otro día que es poca prioridad.

Entonces 

para mañana¹:
- Retomamos singletrans. Mejorar y probarlo.
- Buscar bibliotecas de logging o formas de hacerlo, o craftearme una casera.
  - Pero ojo, como base de código moderna, usando std::print

mañana²:
- Otra de carga almacemiento.
- Implementar undefined.

mañana³:
- Implementar testing para la otra de carga almacenamiento.

mañana⁴:
- Empezar con thumb para lógicas y aritméticas.
- Crear la tabla lut.

# 14 de agosto

para el logging igual merece la pena hacerlo casero. nba usa atom. la más popular es spdlog.

no sé cómo podríamos integrarlo con los test.

de momento sigamos, ya cuestionaré sobre esto al tutor.

mi idea es usar algún tipo de logging. como se hace habitualmente en la industria. pero tener la libertad de alterarlo para modificar su comportamiento por ejemplo si al hacer el testing ocultarlo, mirar qué log ha dado para probar. O más interesante, poder filtrarlo.

tengo pensado en darle un uso muy sencillo. info, warning y error y ya está. y poder categorizarlo. tipo activar todos los logs de instrucciones solo. Pues que cuando pase por fsr o decodifique algo pues qur lo diga. O ignorar esa parte porque ya no interesa.

mira quizás ya lo esté visualizando algo más claro.

necesitamos un gestor de configuración.

y que desde este gestor podamos hacer comprobaciones de que preferencias aplicar. Así por ejemplo si en el testing no interesa mostrar ningún log, pues a tomar viento. O si tiene que escribir en un fichero o no. o si debe hacerlo en ambos. O redireccionar salida de error a la estándar.

La verdad que de pensar todo esto me están dando ganas de usar uno ya hecho.

otra de las bibliotecas para logging son quill, https://github.com/emilk/loguru , boost...

bueno vamos a hacer una cosa. y es que en c++ sabes el coñazo que es cmake y más si es para instalarnos una biblioteca.

de hecho, yo tengo instalado el google test por dnf directamente. Así no me rompo la cabeza ni tampoco en comprobar cada poco tiempo a mano si hay una nueva versión de la biblioteca en línea. Vamos a ir a lo práctico, vamos a recorrer los repositorios de fedora a ver que hay usamos eso. De hecho hay raylib en dnf directamente.

Pues bingo, spdlog ya lo tenía instalado.

Bueno lo dejo para otro día porque estoy cansado. lol.
