/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2011-2019 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Class
    Foam::greyDiffusiveRadiationMixedFvPatchScalarFieldFvDOMP

Description
    This boundary condition provides a grey-diffuse condition for radiation
    intensity, \c I, for use with the finite-volume discrete-ordinates model
    (fvDOMP), in which the radiation temperature is retrieved from the
    temperature field boundary condition.

Usage
    \table
        Property     | Description             | Required    | Default value
        T            | temperature field name  | no          | T
        emissivityMode | emissivity mode: solidRadiation or lookup | yes |
    \endtable

    Example of the boundary condition specification:
    \verbatim
    <patchName>
    {
        type            greyDiffusiveRadiation;
        T               T;
        emissivityMode  solidRadiation;
        value           uniform 0;
    }
    \endverbatim

See also
    Foam::radiationCoupledBase
    Foam::radiationModel
    Foam::radiationModels::fvDOMP
    Foam::mixedFvPatchField

SourceFiles
    greyDiffusiveRadiationMixedFvPatchScalarFieldFvDOMP.C

\*---------------------------------------------------------------------------*/

#ifndef greyDiffusiveRadiationMixedFvPatchScalarFieldFvDOMP_H
#define greyDiffusiveRadiationMixedFvPatchScalarFieldFvDOMP_H

#include "mixedFvPatchFields.H"
#include "radiationCoupledBase.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
        Class greyDiffusiveRadiationMixedFvPatchScalarFieldFvDOMP Declaration
\*---------------------------------------------------------------------------*/

class greyDiffusiveRadiationMixedFvPatchScalarFieldFvDOMP
:
    public mixedFvPatchScalarField,
    public radiationCoupledBase
{
    // Private Data

        //- Name of temperature field
        word TName_;


public:

    //- Runtime type information
    TypeName("greyDiffusiveRadiationFvDOMP");


    // Constructors

        //- Construct from patch and internal field
        greyDiffusiveRadiationMixedFvPatchScalarFieldFvDOMP
        (
            const fvPatch&,
            const DimensionedField<scalar, volMesh>&
        );

        //- Construct from patch, internal field and dictionary
        greyDiffusiveRadiationMixedFvPatchScalarFieldFvDOMP
        (
            const fvPatch&,
            const DimensionedField<scalar, volMesh>&,
            const dictionary&
        );

        //- Construct by mapping given a
        //  greyDiffusiveRadiationMixedFvPatchScalarFieldFvDOMP onto a new patch
        greyDiffusiveRadiationMixedFvPatchScalarFieldFvDOMP
        (
            const greyDiffusiveRadiationMixedFvPatchScalarFieldFvDOMP&,
            const fvPatch&,
            const DimensionedField<scalar, volMesh>&,
            const fvPatchFieldMapper&
        );

        //- Copy constructor
        greyDiffusiveRadiationMixedFvPatchScalarFieldFvDOMP
        (
            const greyDiffusiveRadiationMixedFvPatchScalarFieldFvDOMP&
        );

        //- Construct and return a clone
        virtual tmp<fvPatchScalarField> clone() const
        {
            return tmp<fvPatchScalarField>
            (
                new greyDiffusiveRadiationMixedFvPatchScalarFieldFvDOMP(*this)
            );
        }

        //- Copy constructor setting internal field reference
        greyDiffusiveRadiationMixedFvPatchScalarFieldFvDOMP
        (
            const greyDiffusiveRadiationMixedFvPatchScalarFieldFvDOMP&,
            const DimensionedField<scalar, volMesh>&
        );

        //- Construct and return a clone setting internal field reference
        virtual tmp<fvPatchScalarField> clone
        (
            const DimensionedField<scalar, volMesh>& iF
        ) const
        {
            return tmp<fvPatchScalarField>
            (
                new greyDiffusiveRadiationMixedFvPatchScalarFieldFvDOMP(*this, iF)
            );
        }


    // Member Functions

        // Access

            //- Return the temperature field name
            const word& TName() const
            {
                return TName_;
            }

            //- Return reference to the temperature field name to allow
            //  adjustment
            word& TName()
            {
                return TName_;
            }


        // Mapping functions

            //- Map (and resize as needed) from self given a mapping object
            //  Used to update fields following mesh topology change
            virtual void autoMap(const fvPatchFieldMapper&);

            //- Reverse map the given fvPatchField onto this fvPatchField
            //  Used to reconstruct fields
            virtual void rmap(const fvPatchScalarField&, const labelList&);


        // Evaluation functions

            //- Update the coefficients associated with the patch field
            virtual void updateCoeffs();


        // I-O

            //- Write
            virtual void write(Ostream&) const;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
