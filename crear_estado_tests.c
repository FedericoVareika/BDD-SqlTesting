#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define ArrayLen(arr) (sizeof((arr)) / sizeof((*arr)))

int random_int(int max, int min) {
    int dif = max - min;
    return random() % dif + min;
}

int random_idx(int len) {
    return random() % len;
}

char *nombres[] = {
    "Juan",
    "José Luis",
    "José",
    "María Guadalupe",
    "Francisco",
    "Guadalupe",
    "María",
    "Juana",
    "Antonio",
    "Jesús",
    "Miguel Ángel",
    "Pedro",
    "Alejandro",
    "Manuel",
    "Margarita",
    "María Del Carmen",
    "Juan Carlos",
    "Roberto",
    "Fernando",
    "Daniel",
    "Carlos",
    "Jorge",
    "Ricardo",
    "Miguel",
    "Eduardo",
    "Javier",
    "Rafael",
    "Martín",
    "Raúl",
    "David",
    "Josefina",
    "José Antonio",
    "Arturo",
    "Marco Antonio",
    "José Manuel",
    "Francisco Javier",
    "Enrique",
    "Verónica",
    "Gerardo",
    "María Elena",
    "Leticia",
    "Rosa",
    "Mario",
    "Francisca",
    "Alfredo",
    "Teresa",
    "Alicia",
    "María Fernanda",
    "Sergio",
    "Alberto",
    "Luis",
    "Armando",
    "Alejandra",
    "Martha",
    "Santiago",
    "Yolanda",
    "Patricia",
    "María De Los Ángeles",
    "Juan Manuel",
    "Rosa María",
    "Elizabeth",
    "Gloria",
    "Ángel",
    "Gabriela",
    "Salvador",
    "Víctor Manuel",
    "Silvia",
    "María De Guadalupe",
    "María De Jesús",
    "Gabriel",
    "Andrés",
    "Óscar",
    "Guillermo",
    "Ana María",
    "Ramón",
    "María Isabel",
    "Pablo",
    "Ruben",
    "Antonia",
    "María Luisa",
    "Luis Ángel",
    "María Del Rosario",
    "Felipe",
    "Jorge Jesús",
    "Jaime",
    "José Guadalupe",
    "Julio Cesar",
    "José De Jesús",
    "Diego",
    "Araceli",
    "Andrea",
    "Isabel",
    "María Teresa",
    "Irma",
    "Carmen",
    "Lucía",
    "Adriana",
    "Agustín",
    "María De La Luz",
    "Gustavo",
};

char *genero[] = {
    "Femenino",
    "Masculino",
    "No binario",
};

char *tipo[] = {
    "Tutor",
    "Amigo",
    "Coach",
};

char *ropa[] = {
    "Verano", "Primavera", "Anime", "Oficina", "Fiesta", "Deporte", "Camisetas",
};

char *interes[] = {
    "Juegos",
    "Deportes",
    "Historia",
    "Moda",
};

char *rasgo[] = {
    "Seguro",  "Tímido",    "Energético", "Práctico",
    "Soñador", "Artístico", "Lógico",
};

char *voz[] = {
    "Femenina",
    "Masculina",
};

char vigente[] = {
    'S',
    'N',
};

char *rango_edad[] = {
    "18-24", "25-34", "35-44", "45-54", "55-64", "65 o más",
};

typedef struct {
    int idAsistente;
    char *nombre;
    char *genero;
} Asistente;

typedef struct {
    int idRol;
    char *tipo;
} Rol;

typedef struct {
    int idAsignaRol;
    int idAsistente;
    int idRol;
} AsignaRol;

typedef struct {
    int idConfiguracion;
    char *ropa;
    char *interes;
    char *rasgo;
    char *voz;
    int costoGemas;
    int costoMonenas;
    int idAsistente;
    char vigente;
} Configuracion;

typedef struct {
    int idUsuario;
    char *email;
    char *nombre;
    char *rangoEdad;
    char *fechaRegistro;
    int saldoGemas;
    int saldoMonedas;
    int idAsistente;
} Usuario;

typedef struct {
    int idCompra;
    int idConfiguracion;
    char *email;
    char *fechaCompra;
    int totalGemas;
    int totalMonedas;
} Compra;

#define Tablas()                                                               \
    X(Asistente)                                                               \
    X(Rol)                                                                     \
    X(AsignaRol)                                                               \
    X(Configuracion)                                                           \
    X(Usuario)                                                                 \
    X(Compra)

#define cantidad(a) cant##a
#define gen_random(a) random##a
#define tabla(a) tabla##a

// Random create function declarations
#define X(a) a random##a(int idx);
Tablas();
#undef X

// Global cantidades
#define X(a) int cantidad(a);
Tablas();
#undef X

// Global arrays
#define X(a) a *tabla(a);
Tablas();
#undef X

#define X(a)                                                                   \
    int get_id##a(int idx) {                                                   \
        return tabla(a)[idx].id##a;                                            \
    }
Tablas();
#undef X

Asistente randomAsistente(int idx) {
    Asistente ret = {
        .idAsistente = idx,
        .nombre = nombres[random_idx(ArrayLen(nombres))],
        .genero = genero[random_idx(ArrayLen(genero))],
    };
    return ret;
}

Rol randomRol(int idx) {
    Rol ret = {
        .idRol = idx,
        .tipo = tipo[random_idx(ArrayLen(tipo))],
    };
    return ret;
}

AsignaRol randomAsigna(int idx) {
    AsignaRol ret = {
        .idAsignaRol = idx,
        .idRol = get_idRol(random_idx(cantidad(Rol))),
        .idAsistente = get_idAsistente(random_idx(cantidad(Rol))),
    };
    return ret;
}





#define usage                                                                  \
    "%s [seed] [filename.sql] \n"                                              \
    "   [seed] [filename.sql] [max elementos]\n"                               \
    "   [seed] [filename.sql] [min elementos] [max elementos]\n"

int main(int argc, char **argv) {
    if (argc < 3) {
        printf(usage, argv[0]);
        return 1;
    }

    int seed = atoi(argv[1]);
    srandom(seed);

    FILE *file = fopen(argv[2], "w+");
    assert(file);

    int max_elementos = 1;
    int min_elementos = 1;
    if (argc < 4)
        max_elementos = atoi(argv[3]);
    else {
        max_elementos = atoi(argv[4]);
        min_elementos = atoi(argv[3]);
    }

    // Init cantidades
#define X(a) cantidad(a) = random_int(max_elementos, min_elementos);
    Tablas();
#undef X

    // Init tablas
#define X(a) tabla(a) = malloc(sizeof(a) * cant##a);
    Tablas();
#undef X

    // Randomizar todos
#define X(a)                                                                   \
    for (int i = 0; i < cantidad(a); i++) {                                    \
        tabla(a)[i] = gen_random(a)(i);                                        \
    }
    Tablas();
#undef X

    return 0;
}
