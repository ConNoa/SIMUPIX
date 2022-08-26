#ifndef FILTERKEY_HPP
#define FILTERKEY_HPP


struct FilterKey{
    struct Hash
    {
        // jacked up derivation of bernstiens string hasher
        std::size_t operator()(FilterKey const& key) const
        {
            std::size_t hash = 5381u;
            for (auto c : key.s1)
                hash = (hash << 5) + hash + c;
            for (auto c : key.s2)
                hash = (hash << 5) + hash + c;
            for (auto c : key.s3)
                hash = (hash << 5) + hash + c;
            return hash;
        }
    };

    std::string s1, s2, s3;

    // equivalence determination.
    bool operator ==(FilterKey const& key) const
    {
        return std::tie(s1, s2, s3) == std::tie(key.s1, key.s2, key.s3);
    }
};

#endif
