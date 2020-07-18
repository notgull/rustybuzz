/*
 * Copyright © 2009  Red Hat, Inc.
 *
 *  This is part of HarfBuzz, a text shaping library.
 *
 * Permission is hereby granted, without written agreement and without
 * license or royalty fees, to use, copy, modify, and distribute this
 * software and its documentation for any purpose, provided that the
 * above copyright notice and the following two paragraphs appear in
 * all copies of this software.
 *
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE TO ANY PARTY FOR
 * DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES
 * ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN
 * IF THE COPYRIGHT HOLDER HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 *
 * THE COPYRIGHT HOLDER SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING,
 * BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS
 * ON AN "AS IS" BASIS, AND THE COPYRIGHT HOLDER HAS NO OBLIGATION TO
 * PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.
 *
 * Red Hat Author(s): Behdad Esfahbod
 */

#ifndef HB_H_IN
#error "Include <hb.h> instead."
#endif

#ifndef HB_FONT_H
#define HB_FONT_H

#include "hb-common.h"
#include "hb-face.h"

HB_BEGIN_DECLS

typedef struct hb_font_t hb_font_t;

/* font and glyph extents */

/* Note that typically ascender is positive and descender negative in coordinate systems that grow up. */
typedef struct hb_font_extents_t
{
    hb_position_t ascender;  /* typographic ascender. */
    hb_position_t descender; /* typographic descender. */
    hb_position_t line_gap;  /* suggested line spacing gap. */
    /*< private >*/
    hb_position_t reserved9;
    hb_position_t reserved8;
    hb_position_t reserved7;
    hb_position_t reserved6;
    hb_position_t reserved5;
    hb_position_t reserved4;
    hb_position_t reserved3;
    hb_position_t reserved2;
    hb_position_t reserved1;
} hb_font_extents_t;

/* Note that height is negative in coordinate systems that grow up. */
typedef struct hb_glyph_extents_t
{
    hb_position_t x_bearing; /* left side of glyph from origin. */
    hb_position_t y_bearing; /* top side of glyph from origin. */
    hb_position_t width;     /* distance from left to right side. */
    hb_position_t height;    /* distance from top to bottom side. */
} hb_glyph_extents_t;

/* func dispatch */

HB_EXTERN hb_bool_t hb_font_get_h_extents(hb_font_t *font, hb_font_extents_t *extents);
HB_EXTERN hb_bool_t hb_font_get_v_extents(hb_font_t *font, hb_font_extents_t *extents);

HB_EXTERN hb_bool_t hb_font_get_nominal_glyph(hb_font_t *font, hb_codepoint_t unicode, hb_codepoint_t *glyph);
HB_EXTERN hb_bool_t hb_font_get_variation_glyph(hb_font_t *font,
                                                hb_codepoint_t unicode,
                                                hb_codepoint_t variation_selector,
                                                hb_codepoint_t *glyph);

HB_EXTERN unsigned int hb_font_get_nominal_glyphs(hb_font_t *font,
                                                  unsigned int count,
                                                  const hb_codepoint_t *first_unicode,
                                                  unsigned int unicode_stride,
                                                  hb_codepoint_t *first_glyph,
                                                  unsigned int glyph_stride);

HB_EXTERN hb_position_t hb_font_get_glyph_h_advance(hb_font_t *font, hb_codepoint_t glyph);
HB_EXTERN hb_position_t hb_font_get_glyph_v_advance(hb_font_t *font, hb_codepoint_t glyph);

HB_EXTERN void hb_font_get_glyph_h_advances(hb_font_t *font,
                                            unsigned int count,
                                            const hb_codepoint_t *first_glyph,
                                            unsigned glyph_stride,
                                            hb_position_t *first_advance,
                                            unsigned advance_stride);
HB_EXTERN void hb_font_get_glyph_v_advances(hb_font_t *font,
                                            unsigned int count,
                                            const hb_codepoint_t *first_glyph,
                                            unsigned glyph_stride,
                                            hb_position_t *first_advance,
                                            unsigned advance_stride);

HB_EXTERN hb_bool_t hb_font_get_glyph_extents(hb_font_t *font, hb_codepoint_t glyph, hb_glyph_extents_t *extents);

HB_EXTERN hb_bool_t hb_font_get_glyph_contour_point(
    hb_font_t *font, hb_codepoint_t glyph, unsigned int point_index, hb_position_t *x, hb_position_t *y);

HB_EXTERN hb_bool_t hb_font_get_glyph_name(hb_font_t *font, hb_codepoint_t glyph, char *name, unsigned int size);

/* high-level funcs, with fallback */

/* Calls either hb_font_get_nominal_glyph() if variation_selector is 0,
 * otherwise calls hb_font_get_variation_glyph(). */
HB_EXTERN hb_bool_t hb_font_get_glyph(hb_font_t *font,
                                      hb_codepoint_t unicode,
                                      hb_codepoint_t variation_selector,
                                      hb_codepoint_t *glyph);

HB_EXTERN void hb_font_get_extents_for_direction(hb_font_t *font, hb_direction_t direction, hb_font_extents_t *extents);
HB_EXTERN void hb_font_get_glyph_advance_for_direction(
    hb_font_t *font, hb_codepoint_t glyph, hb_direction_t direction, hb_position_t *x, hb_position_t *y);
HB_EXTERN void hb_font_get_glyph_advances_for_direction(hb_font_t *font,
                                                        hb_direction_t direction,
                                                        unsigned int count,
                                                        const hb_codepoint_t *first_glyph,
                                                        unsigned glyph_stride,
                                                        hb_position_t *first_advance,
                                                        unsigned advance_stride);
HB_EXTERN void hb_font_get_glyph_origin_for_direction(
    hb_font_t *font, hb_codepoint_t glyph, hb_direction_t direction, hb_position_t *x, hb_position_t *y);
HB_EXTERN void hb_font_add_glyph_origin_for_direction(
    hb_font_t *font, hb_codepoint_t glyph, hb_direction_t direction, hb_position_t *x, hb_position_t *y);
HB_EXTERN void hb_font_subtract_glyph_origin_for_direction(
    hb_font_t *font, hb_codepoint_t glyph, hb_direction_t direction, hb_position_t *x, hb_position_t *y);

HB_EXTERN hb_bool_t hb_font_get_glyph_extents_for_origin(hb_font_t *font,
                                                         hb_codepoint_t glyph,
                                                         hb_direction_t direction,
                                                         hb_glyph_extents_t *extents);

HB_EXTERN hb_bool_t hb_font_get_glyph_contour_point_for_origin(hb_font_t *font,
                                                               hb_codepoint_t glyph,
                                                               unsigned int point_index,
                                                               hb_direction_t direction,
                                                               hb_position_t *x,
                                                               hb_position_t *y);

/* Generates gidDDD if glyph has no name. */
HB_EXTERN void hb_font_glyph_to_string(hb_font_t *font, hb_codepoint_t glyph, char *s, unsigned int size);

/*
 * hb_font_t
 */

/* Fonts are very light-weight objects */

HB_EXTERN hb_font_t *hb_font_create(hb_face_t *face);

HB_EXTERN hb_font_t *hb_font_get_empty(void);

HB_EXTERN hb_font_t *hb_font_reference(hb_font_t *font);

HB_EXTERN void hb_font_destroy(hb_font_t *font);

HB_EXTERN hb_bool_t hb_font_is_immutable(hb_font_t *font);

HB_EXTERN hb_face_t *hb_font_get_face(hb_font_t *font);

/*
 * A zero value means "no hinting in that direction"
 */
HB_EXTERN void hb_font_set_ppem(hb_font_t *font, unsigned int x_ppem, unsigned int y_ppem);

HB_EXTERN void hb_font_get_ppem(hb_font_t *font, unsigned int *x_ppem, unsigned int *y_ppem);

/*
 * Point size per EM.  Used for optical-sizing in CoreText.
 * A value of zero means "not set".
 */
HB_EXTERN void hb_font_set_ptem(hb_font_t *font, float ptem);

HB_EXTERN float hb_font_get_ptem(hb_font_t *font);

HB_EXTERN void
hb_font_set_variations(hb_font_t *font, const hb_variation_t *variations, unsigned int variations_length);

HB_EXTERN void hb_font_set_var_coords_design(hb_font_t *font, const float *coords, unsigned int coords_length);

HB_EXTERN void hb_font_set_var_coords_normalized(hb_font_t *font,
                                                 const int *coords, /* 2.14 normalized */
                                                 unsigned int coords_length);

HB_EXTERN const int *hb_font_get_var_coords_normalized(hb_font_t *font, unsigned int *length);

HB_EXTERN void hb_font_set_var_named_instance(hb_font_t *font, unsigned instance_index);

HB_END_DECLS

#endif /* HB_FONT_H */
