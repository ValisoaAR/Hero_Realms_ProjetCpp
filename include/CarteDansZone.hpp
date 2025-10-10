#pragma once

class CarteDansZone {
public:
    int id;
    int carte_id;
    int zone_id;
    int ordre;

    CarteDansZone(int id, int carte_id, int zone_id, int ordre);
};
