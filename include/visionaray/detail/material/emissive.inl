// This file is distributed under the MIT license.
// See the LICENSE file for details.

namespace visionaray
{

//-------------------------------------------------------------------------------------------------
// Public interface
//

template <typename T>
VSNRAY_FUNC
inline spectrum<T> emissive<T>::ambient() const
{
    return spectrum<T>();
}

template <typename T>
template <typename SR>
VSNRAY_FUNC
inline spectrum<typename SR::scalar_type> emissive<T>::shade(SR const& sr) const
{
    return from_rgb(sr.tex_color) * ce_ * ls_;
}

template <typename T>
template <typename SR, typename U, typename Sampler>
VSNRAY_FUNC
inline spectrum<U> emissive<T>::sample(
        SR const&       shade_rec,
        vector<3, U>&   refl_dir,
        U&              pdf,
        Sampler&        sampler
        ) const
{
    VSNRAY_UNUSED(refl_dir); // TODO?
    VSNRAY_UNUSED(sampler);
    pdf = U(1.0);
    return shade(shade_rec);
}

// --- deprecated begin -----------------------------------

template <typename T>
VSNRAY_FUNC
inline void emissive<T>::set_ce(spectrum<T> const& ce)
{
    ce_ = ce;
}

template <typename T>
VSNRAY_FUNC
inline spectrum<T> emissive<T>::get_ce() const
{
    return ce_;
}

template <typename T>
VSNRAY_FUNC
inline void emissive<T>::set_ls(T ls)
{
    ls_ = ls;
}

template <typename T>
VSNRAY_FUNC
inline T emissive<T>::get_ls() const
{
    return ls_;
}

// --- deprecated end -------------------------------------

template <typename T>
VSNRAY_FUNC
inline spectrum<T>& emissive<T>::ce()
{
    return ce_;
}

template <typename T>
VSNRAY_FUNC
inline spectrum<T> const& emissive<T>::ce() const
{
    return ce_;
}

template <typename T>
VSNRAY_FUNC
inline T& emissive<T>::ls()
{
    return ls_;
}

template <typename T>
VSNRAY_FUNC
inline T const& emissive<T>::ls() const
{
    return ls_;
}

} // visionaray
