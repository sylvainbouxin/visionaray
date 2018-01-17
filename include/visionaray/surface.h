// This file is distributed under the MIT license.
// See the LICENSE file for details.

#pragma once

#ifndef VSNRAY_SURFACE_H
#define VSNRAY_SURFACE_H 1

#include "detail/macros.h"
#include "detail/tags.h"
#include "math/vector.h"
#include "material.h"
#include "shade_record.h"

namespace visionaray
{

template <typename ...Args>
struct surface;

template <typename N, typename M>
struct surface<N, M>
{
    using scalar_type = typename M::scalar_type;

    N geometric_normal;
    N shading_normal;
    M material;

    template <typename U>
    VSNRAY_FUNC
    spectrum<scalar_type> shade(vector<3, U> const& view_dir, vector<3, U> const& light_dir, vector<3, U> const& light_intensity)
    {
        shade_record<U> shade_rec;
        shade_rec.normal           = shading_normal;
        shade_rec.geometric_normal = geometric_normal;
        shade_rec.view_dir         = view_dir;
        shade_rec.tex_color        = vector<3, U>(1.0f);
        shade_rec.light_dir        = light_dir;
        shade_rec.light_intensity  = light_intensity;

        return material.shade(shade_rec);
    }

    template <typename U, typename S /* sampler */>
    VSNRAY_FUNC
    spectrum<scalar_type> sample(vector<3, U> const& view_dir, vector<3, U>& refl_dir, U& pdf, S& sampler)
    {
        shade_record<U> shade_rec;
        shade_rec.normal           = shading_normal;
        shade_rec.geometric_normal = geometric_normal;
        shade_rec.view_dir         = view_dir;
        shade_rec.tex_color        = vector<3, U>(1.0f);

        return material.sample(shade_rec, refl_dir, pdf, sampler);
    }
};

template <typename N, typename C, typename M>
struct surface<N, C, M>
{
    using scalar_type = typename M::scalar_type;

    N geometric_normal;
    N shading_normal;
    C tex_color;
    M material;

    template <typename U>
    VSNRAY_FUNC
    spectrum<scalar_type> shade(vector<3, U> const& view_dir, vector<3, U> const& light_dir, vector<3, U> const& light_intensity)
    {
        shade_record<U> shade_rec;
        shade_rec.normal           = shading_normal;
        shade_rec.geometric_normal = geometric_normal;
        shade_rec.view_dir         = view_dir;
        shade_rec.tex_color        = tex_color;
        shade_rec.light_dir        = light_dir;
        shade_rec.light_intensity  = light_intensity;

        return material.shade(shade_rec);
    }

    template <typename U, typename S /* sampler */>
    VSNRAY_FUNC
    spectrum<scalar_type> sample(vector<3, U> const& view_dir, vector<3, U>& refl_dir, U& pdf, S& sampler)
    {
        shade_record<U> shade_rec;
        shade_rec.normal           = shading_normal;
        shade_rec.geometric_normal = geometric_normal;
        shade_rec.view_dir         = view_dir;
        shade_rec.tex_color        = tex_color;

        return material.sample(shade_rec, refl_dir, pdf, sampler);
    }
};

} // visionaray

#include "detail/surface.inl"

#endif // VSNRAY_SURFACE_H
