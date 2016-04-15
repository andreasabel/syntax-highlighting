/*
    Copyright (C) 2016 Volker Krause <vkrause@kde.org>

    This program is free software; you can redistribute it and/or modify it
    under the terms of the GNU Library General Public License as published by
    the Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    This program is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
    License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef KATESYNTAX_RULE_H
#define KATESYNTAX_RULE_H

#include "keywordlist.h"

#include <QString>
#include <QVector>

class QXmlStreamReader;

namespace KateSyntax {

class Rule
{
public:
    Rule();
    virtual ~Rule();

    bool load(QXmlStreamReader &reader);

    int match(const QString &text, int offset);

    static Rule* create(const QStringRef &name);

protected:
    virtual bool doLoad(QXmlStreamReader &reader) = 0;
    virtual int doMatch(const QString &text, int offset) = 0;

private:
    Q_DISABLE_COPY(Rule)

    QString m_attribute;
    QString m_context;
    QVector<Rule*> m_subRules;
    bool m_firstNonSpace;
};


class DetectChar : public Rule
{
protected:
    bool doLoad(QXmlStreamReader & reader) override;
    int doMatch(const QString & text, int offset) override;

private:
    QChar m_char;
};

class KeywordListRule : public Rule
{
public:
    QString listName() const;
    void setKeywordList(const KeywordList &list);

protected:
    bool doLoad(QXmlStreamReader & reader) override;
    int doMatch(const QString & text, int offset) override;

private:
    QString m_listName;
    KeywordList m_keywordList;
};


}

#endif // KATESYNTAX_RULE_H
