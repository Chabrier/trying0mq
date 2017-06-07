/**
  * @file wwdmDt.cpp
  * @author ...
  * ...
  */

/*
 * @@tagdynamic@@
 * @@tagdepends: vle.discrete-time @@endtagdepends
*/
#include <zmq.hpp>
#include <string>
#include <iostream>
#include <vle/DiscreteTime.hpp>
//includes
namespace vd = vle::devs;

namespace vv = vle::value;

namespace vle {
namespace discrete_time {
namespace wwdmDt {

class wwdmDt : public DiscreteTimeDyn
{
public:
wwdmDt(
    const vd::DynamicsInit& init,
    const vd::InitEventList& evts)
    : DiscreteTimeDyn(init, evts),
      context(1) , socket(context, ZMQ_REP)
{
    std::cout << "inside cosnt" << std::endl;
     socket.bind ("tcp://*:5555");

    Eb.init(this, "Eb", evts);
    Eimax.init(this, "Eimax", evts);
    K.init(this, "K", evts);
    Lmax.init(this, "Lmax", evts);
    A.init(this, "A", evts);
    B.init(this, "B", evts);
    TI.init(this, "TI", evts);
    Tmin.init(this, "Tmin", evts);
    Tmax.init(this, "Tmax", evts);
    RG.init(this, "RG", evts);
    ST.init(this, "ST", evts);
    LAI.init(this, "LAI", evts);
    U.init(this, "U", evts);
    Tr.init(this, "Tr", evts);
    Tmean.init(this, "Tmean", evts);
    PAR.init(this, "PAR", evts);
//constructor

Tr.init_value((1 / B()) * std::log(1 + std::exp(A() * TI())));

}

virtual ~wwdmDt()
{}

    void compute(const vle::devs::Time& /* t */)
{
           zmq::message_t request;
           std::cout << "waiting" <<std::endl;

        //  Wait for next request from client
        socket.recv (&request);
        std::cout << "Received Hello " << request.size()<< " "<< (const char*)request.data() << std::endl;

PAR = 0.5 * 0.01 * RG();

Tmean = std::max(0.0, (Tmin() + Tmax()) / 2);

if (ST() == -1) {
ST = 0;
} else if (ST() == -2) {
ST = 10000;
} else {
ST = ST() + Tmean();
}

LAI = std::max(0.0, Lmax() * ((1 / (1 + std::exp(-A() * (ST() - TI())))) -
                                std::exp(B() * (ST() - Tr()))));

U = U(-1) + Eb() * Eimax() * (1 - std::exp(-K() * LAI())) * PAR();


   //  Send reply back to client
        zmq::message_t reply (5);
        memcpy (reply.data (), "World", 5);
        socket.send (reply);

}

    Var Eb;
    Var Eimax;
    Var K;
    Var Lmax;
    Var A;
    Var B;
    Var TI;
    Var Tmin;
    Var Tmax;
    Var RG;
    Var ST;
    Var LAI;
    Var U;
    Var Tr;
    Var Tmean;
    Var PAR;

//user

    zmq::context_t context;
    zmq::socket_t socket;
};

} // namespace wwdmDt
} // namespace discrete_time
} // namespace vle

DECLARE_DYNAMICS(vle::discrete_time::wwdmDt::wwdmDt)
