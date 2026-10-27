/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 15:40:27 by cycolonn          #+#    #+#             */
/*   Updated: 2026/10/27 15:40:29 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

// --- RÉINITIALISATION ---
# define RESET          "\001\033[0m\002"

// --- COULEURS STANDARDS (Sombres) ---
# define BLACK          "\001\033[0;30m\002"
# define RED            "\001\033[0;31m\002"
# define GREEN          "\001\033[0;32m\002"
# define YELLOW         "\001\033[0;33m\002"
# define BLUE           "\001\033[0;34m\002"
# define PURPLE         "\001\033[0;35m\002"
# define CYAN           "\001\033[0;36m\002"
# define WHITE          "\001\033[0;37m\002"

// --- COULEURS GRAS (Bold) ---
# define B_RED          "\001\033[1;31m\002"
# define B_GREEN        "\001\033[1;32m\002"
# define B_YELLOW       "\001\033[1;33m\002"
# define B_BLUE         "\001\033[1;34m\002"
# define B_PURPLE       "\001\033[1;35m\002"
# define B_CYAN         "\001\033[1;36m\002"
# define B_WHITE        "\001\033[1;37m\002"

// --- COULEURS LIGHT / HIGH INTENSITY ---
# define L_RED          "\001\033[0;91m\002"
# define L_GREEN        "\001\033[0;92m\002"
# define L_YELLOW       "\001\033[0;93m\002"
# define L_BLUE         "\001\033[0;94m\002"
# define L_PURPLE       "\001\033[0;95m\002"
# define L_CYAN         "\001\033[0;96m\002"
# define L_WHITE        "\001\033[0;97m\002"

// --- COULEURS BOLD LIGHT (Gras + Lumineux) ---
# define BL_RED         "\001\033[1;91m\002"
# define BL_GREEN       "\001\033[1;92m\002"
# define BL_YELLOW      "\001\033[1;93m\002"
# define BL_BLUE        "\001\033[1;94m\002"
# define BL_PURPLE      "\001\033[1;95m\002"
# define BL_CYAN        "\001\033[1;96m\002"
# define BL_WHITE       "\001\033[1;97m\002"

// --- BACKGROUNDS ---
# define BG_RED         "\001\033[41m\002"
# define BG_GREEN       "\001\033[42m\002"
# define BG_YELLOW      "\001\033[43m\002"
# define BG_BLUE        "\001\033[44m\002"

// --- COULEURS ÉTENDUES (Palette 256 couleurs) ---
# define MINT           "\001\033[38;5;121m\002" // Vert menthe
# define CORAL          "\001\033[38;5;203m\002" // Corail
# define STEEL          "\001\033[38;5;110m\002" // Bleu acier
# define LAVENDER       "\001\033[38;5;147m\002" // Lavande
# define ICE_BLUE       "\001\033[38;5;117m\002" // Bleu glace
# define GOLD           "\001\033[38;5;214m\002" // Or
# define ORANGE         "\001\033[38;5;208m\002" // Orange
# define PINK           "\001\033[38;5;212m\002" // Rose
# define LIME           "\001\033[38;5;154m\002" // Citron vert
# define TURQUOISE      "\001\033[38;5;45m\002"  // Turquoise
# define SILVER         "\001\033[38;5;249m\002" // Argent
# define SALMON         "\001\033[38;5;209m\002" // Saumon

#endif