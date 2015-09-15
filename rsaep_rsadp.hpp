/** -*- c-basic-offset: 3 -*- 
 *
 * ENSICAEN
 * 6 Boulevard Maréchal Juin 
 * F-14050 Caen Cedex
 * 
 * Ce fichier est l'oeuvre d'élèves de l'ENSI de Caen. Il ne peut être 
 * reproduit, utilisé ou modifié sans l'avis express de ses auteurs.
 * 
 */ 

/** 
 * @author Corentin MARCIAU	<corentin.marciau@ecole.ensicaen.fr>
 *
 * @version 1.0.0 / 15-09-2015
 * @todo 
 * @bug 
 */

/** 
 * @file rsaep_rsadp.hpp
 * @brief 
 *
 * 
 */

#ifndef _RSAEP_RSADP_HPP_
#define _RSAEP_RSADP_HPP_

#include "keys.hpp"
#include "rsa_pub_key.hpp"
#include "rsa_priv_key.hpp"

#include <cmath>
#include <boost/multiprecision/gmp.hpp>
#include <string>

namespace basics {

using namespace boost::multiprecision;

typedef mpz_int int_type;

class Rsaep_rsadp {

private:
   Keys keys_;

   int_type powModulus(int_type base, int_type exp, int_type mod) 
   {
      if (exp == 0) return 1;
      if (base == 0) return 0;
      if (mod <= 0) {
         std::cout << "null or negative modulus" << std::endl;
         return -1;
      }

      int_type acc = base;

      for (int i=1; i<exp; i++) {
         acc = (acc * base) % mod;
      }
      
      return acc;
   }
   
   
public:
   Rsaep_rsadp(Keys keys) : keys_(keys)
   {
   }

   int_type rsaep(int_type message) 
   {
      std::cout << "    ciphering : " << message << std::endl;
      
      Rsa_pub_key key = keys_.getPublicKey();
      
      if (message < 0 || message >= key.getModulus()) {
         std::cout << "message representative out of range" << std::endl;
      }

      std::cout << "    computing : ( " << message << " exp " << key.getExponent() << " ) mod " << key.getModulus() << std::endl;
      
      // RSA : c = m^e mod n
      int_type c = powModulus(message, key.getExponent(), key.getModulus());

      return c;
   }
   
   int_type rsadp(int_type cipher_text) 
   {
      Rsa_priv_key key = keys_.getPrivateKey();
      
      if (cipher_text < 0 || cipher_text >= key.getModulus()) {
         std::cout << "ciphertext representative out of range" << std::endl;
      }
      
      // RSA : m = c^d mod n
      int_type m = powModulus(cipher_text, key.getExponent(), key.getModulus());

      return m;
   }
   
   
};

} //namespace

#endif
