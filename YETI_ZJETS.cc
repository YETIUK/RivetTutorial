// -*- C++ -*-
#include "Rivet/Analyses/MC_JetAnalysis.hh"
#include "Rivet/Projections/ZFinder.hh"
#include "Rivet/Projections/FastJets.hh"

namespace Rivet {


    /// @brief MC validation analysis for Z + jets events
    class YETI_ZJETS : public Analysis {
        public:

            /// Default constructor
            YETI_ZJETS(const string& name = "YETI_ZJETS")
                : Analysis(name) { }


            /// @name Analysis methods
            //@{

            /// Initialize
            void init() {
                // all final state particles
                FinalState fs;

                // fiducial cut for our electrons
                Cut cut = Cuts::abseta < 3.5 && Cuts::pT > 25*GeV;

                // instantiate our ZFinder, which searches for pairs
                // of electrons (both passing our fiducial electron cut)
                // with 65 GeV < invariant mass < 115 GeV.
                // the last three arguments are related to dressing
                // electrons with nearby photons.
                ZFinder zfinder(fs, cut, PID::ELECTRON, 65*GeV, 115*GeV,
                        0.2, ZFinder::CLUSTERNODECAY, ZFinder::TRACK);

                // book the ZFinder projection
                addProjection(zfinder, "ZFinder");

                // the jet finding projection
                // built from all final state particles that did not pass
                // our ZFinder criteria.
                // here we ask for anti-kt jets with R = 0.4
                FastJets jetpro(zfinder.remainingFinalState(), FastJets::ANTIKT, 0.4);

                addProjection(jetpro, "Jets");

                // book histograms which we will store
                _h_Z_mass = bookHisto1D("Z_mass", 50, 50*GeV, 125*GeV);
                _h_Z_pt = bookHisto1D("Z_pt", 50, 0, 50*GeV);
                _h_Z_jet1_dR = bookHisto1D("Z_jet1_dR", 25, 0.5, 7.0);
            }



            /// Do the analysis
            void analyze(const Event & e) {

                const ZFinder& zfinder = applyProjection<ZFinder>(e, "ZFinder");
                if (zfinder.bosons().size() != 1) vetoEvent;

                // all jets with pT > 25 GeV, ordered by pT
                const Jets& jets = applyProjection<FastJets>(e, "Jets").jetsByPt(25*GeV);
                if (jets.size() < 1) vetoEvent;

                const double weight = e.weight();

                // the four momentum of the Z
                const FourMomentum& zmom = zfinder.bosons()[0].momentum();

                // the four momentum of the leading jet
                const FourMomentum& jmom = jets[0].momentum();

                _h_Z_mass->fill(zmom.mass(), weight);
                _h_Z_pt->fill(zmom.pT(), weight);
                _h_Z_jet1_dR->fill(deltaR(zmom, jmom), weight);

            }

            /// Finalize
            void finalize() {
                scale(_h_Z_mass, crossSection()/picobarn/sumOfWeights());
                scale(_h_Z_pt, crossSection()/picobarn/sumOfWeights());
                scale(_h_Z_jet1_dR, crossSection()/picobarn/sumOfWeights());
            }

            //@}


        private:

            /// @name Histograms
            //@{
            Histo1DPtr _h_Z_mass;
            Histo1DPtr _h_Z_pt;
            Histo1DPtr _h_Z_jet1_dR;
            //@}

    };


    // The hooks for the plugin system
    DECLARE_RIVET_PLUGIN(YETI_ZJETS);

}
