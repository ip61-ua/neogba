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

  - Luego me puse a refactorizar el código para una versión branchless el caso de recursivo branch 
