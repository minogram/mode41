#include "HpglReference.h"
#include "HpglCommandInfo.h"
#include <QtCore>

HpglReference::HpglReference()
{
    reset();
}

void HpglReference::add(const QString &name, const QString &param, const QString &desc)
{
    m_known.insert(name, HpglCommandInfo(name, param, desc));
}

void HpglReference::ignore(const QString &name)
{
    m_ignore << name;
}

void HpglReference::reset()
{
    m_known.clear();
    m_ignore.clear();
}

bool HpglReference::canIgnore(const QString &name)
{
    return m_ignore.contains(name);
}

bool HpglReference::hasInfo(const QString &name)
{
    return m_known.contains(name);
}

const QString &HpglReference::param(const QString &name)
{
    return m_known.value(name).param();
}

void HpglReference::build0()
{
    // HPGL command reference
    // http://paulbourke.net/dataformats/hpgl/

    // ======= formats
    // p* = points list
    // n = integer number
    // n* = integer array
    // f* = float array

    add("PU", "p*", "pen up");
    add("PD", "p*", "pen down");
    add("PA", "p*", "pen absolute");
    add("PR", "p*", "pen relative");
    add("SP", "n", "select pen");

    add("IN", "", "initialize");
    add("DF", "", "default");
    add("PG", "", "page feed"); // PG | PG n
    add("VS", "n*", "velocity select"); // VS speed (, pennumber)
    add("ZF", "", "?");
    add("NR", "", "not ready");
    add("ZO", "n", "?"); // ZO0
    add("LT", "n*", "line type patternnumber(,patternlength)");
    add("CI", "f*", "circle radius(,tolerance)");

    ignore("ZF");     // ZF20,3; in ioline plotter manual, ZF is no longer supported. ignore this.
    ignore("VS");   // velocity select

    //================= unknown
    // PI
    // NP
    // BB
    // LT
    // CI circle
}
