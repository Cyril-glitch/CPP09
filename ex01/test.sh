#!/usr/bin/env bash

BIN="./RPN"

if [ ! -f "$BIN" ]; then
    echo "Erreur : binaire $BIN introuvable. Compile d'abord !"
    exit 1
fi

run_test() {
    local desc="$1"
    local expr="$2"
    local expected="$3"

    output=$($BIN "$expr" 2>&1)
    status=$?

    echo "----------------------------------------"
    echo "Test : $desc"
    echo "Entrée : \"$expr\""
    echo "Attendu : $expected"
    echo "Obtenu  : $output (code retour: $status)"
}

# Cas nominaux du sujet
run_test "Sujet 1" "8 9 * 9 - 9 - 9 - 4 - 1 +" "42"
run_test "Sujet 2" "7 7 * 7 -" "42"
run_test "Sujet 3" "1 2 * 2 / 2 * 2 4 - +" "0"

# Cas d'erreurs (doivent afficher 'Error')
run_test "Division par zéro" "5 0 /" "Error"
run_test "Nombre négatif ou > 9 en entrée" "(1 + 1)" "Error"
run_test "Opérateur sans assez d'opérandes" "1 +" "Error"
run_test "Reste trop d'opérandes à la fin" "1 2 3 +" "Error"
run_test "Chaîne vide" "" "Error"
run_test "Caractères invalides" "1 a +" "Error"