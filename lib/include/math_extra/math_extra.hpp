/**
 * INSERT LICENCE INFORMATION HERE 
 */ 

/**
 * @author Corentin MARCIAU	<corentin@marciau.fr>
 */

/**
 * @file math_extra.hpp
 */

#ifndef _MATH_EXTRA_HPP_
#define _MATH_EXTRA_HPP_

#include <boost/multiprecision/gmp.hpp>
#include <boost/multiprecision/integer.hpp>

namespace basics {

typedef boost::multiprecision::mpz_int int_type;

/** 
 * Fonction calculant l'inverse modulaire d'un entier e
 * modulo un entier phi.
 *
 * C'est à dire un autre entier d tel que e * d == 1 mod phi
 *
 * Utilisé lors de la génération des clefs RSA pour calculer 
 * l'inverse de e l'exposant de chiffrement modulo phi, l'indicatrice
 * d'Euler du module N.
 *
 * @param    int_type     e     un entier compris entre 1 et phi - 1
 * @param    int_type     phi   un entier module
 * @return   int_type     d     un entier tel que (e * d) % phi == 1
 */
int_type inverse(int_type e, int_type phi);

/** 
 * Fonction d'exponentiation modulaire rapide pour RSA.
 * 
 * Étant donné trois entiers e, k et n, calcule efficactement
 * le résultat de pow(e, k) % n.
 *
 * S'agissant de grands nombres, il est impossible de calculer
 * directement pow(e, k) puis de calculer le modulo. Il faut donc
 * utiliser une astuce basée sur le fait que :
 *
 *    a*b mod N == ( (a mod N) * (b mod N) ) mod N
 *
 * Avec ceci, il faut un petit jeu sur les puissances pour de 
 * pas avoir un nombre incalculable de modulos à déterminer.
 *
 * @param   int_type  base    l'entier à exponentier
 * @param   int_type  exp     l'exposant, un entier très grand
 * @param   int_type  mod     le module d'exponentiation
 * @return  int_type  m       l'entier tel que m == pow(e,k) % N
 */
int_type 
powModulus(const int_type& base, 
           const int_type& exp, 
           const int_type& mod);

} // namespace

#endif