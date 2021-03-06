double find_angle(point A, point B, point C) { // find angle of <ABC
    // angle find in degree for radiant use x*180/PI
    double x = B.dis(C);
    double y = C.dis(A);
    double z = A.dis(B);
    return acos((z*z + x*x - y*y)/(2*z*x));
}

int turn( point O , point A , point B) { //

    double res = (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
    if( res < 0 ) return -1 ; // O->A->B is a right turn
    if( res > 0 ) return  1 ; // O->A->B is a left turn
    return 0; // O->A->B is a straight line / co-linear
}

db lattice_pts(point a,point b) {
    if (a.x == b.x) return llabs(a.y - b.y) + 1;
    return __gcd(llabs(a.y - b.y), llabs(a.x - b.x)) + 1;
}

bool onsegment(const point &p1, const point &p2, const point &p3) {
    point pmn, pmx;
    pmn.x = min(p1.x, p2.x), pmn.y = min(p1.y, p2.y);
    pmx.x = max(p1.x, p2.x), pmx.y = max(p1.y, p2.y);
    return pmn.x <= p3.x && p3.x <= pmx.x && pmn.y <= p3.y && p3.y <= pmx.y;
}

bool Intersect(const point &p1, const point &p2, const point &p3, const point &p4, bool &on) { //segent segment intersection
    ll d1, d2, d3, d4;
    d1 = turn(p3, p4, p1);
    d2 = turn(p3, p4, p2);
    d3 = turn(p1, p2, p3);
    d4 = turn(p1, p2, p4);
    on = false;
    if(((d1 < 0 && d2 > 0) || (d1 > 0 && d2 < 0)) && ((d3 < 0 && d4 > 0) || (d3 > 0 && d4 < 0))) return true;
    if( !d3 && onsegment(p1, p2, p3)) {
        on = true;
        return true;
    }
    if( !d4 && onsegment(p1, p2, p4)) return true;
    if( !d1 && onsegment(p3, p4, p1)) return true;
    if( !d2 && onsegment(p3, p4, p2)) return true;
    return false;
}
