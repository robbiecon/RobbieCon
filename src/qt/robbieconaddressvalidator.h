// Copyright (c) 2011-2014 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ROBBIECON_QT_ROBBIECONADDRESSVALIDATOR_H
#define ROBBIECON_QT_ROBBIECONADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class RobbieconAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit RobbieconAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** Robbiecon address widget validator, checks for a valid robbiecon address.
 */
class RobbieconAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit RobbieconAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

#endif // ROBBIECON_QT_ROBBIECONADDRESSVALIDATOR_H
