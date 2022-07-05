// Commande: NAMES
// Paramètres: [<canal>{,<canal>}]

// En utilisant la commande NAMES, un utilisateur peut obtenir la liste des pseudonymes 
// visibles sur n'importe quel canal qu'il peut voir. Les noms de canaux qu'il peut voir 
// sont ceux qui ne sont ni privés (+p), ni secrets (+s), ou ceux sur lesquels il est 
// actuellement. Le paramètre <canal> spécifie quels sont les canaux dont l'information 
// est voulue, s'ils sont valides. Il n'y a pas de message d'erreur pour les noms de canaux invalides.

// Si le paramètre <canal> n'est pas donné, la liste de tous les canaux et de leurs 
// occupants est renvoyée. A la fin de cette liste, sont listés les utilisateurs visibles, 
// mais qui n'appartiennent à aucun canal visible. Ils sont listés comme appartenant au 'canal' "*".

// Réponses numériques:

//            RPL_NAMREPLY                    RPL_ENDOFNAMES

// Exemples:

//     NAMES #twilight_zone,#42 ; liste les utilisateurs visibles sur #twilight_zone et #42, si ces canaux vous sont visibles.
//     NAMES ; liste tous les canaux, et tous les utilisateurs visibles. 
