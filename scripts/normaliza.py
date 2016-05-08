# coding=utf-8
import csv
from random import shuffle


def normaliza_espaco(string):
    """
    substituis espaços em sequencia por um único espaço.
    EX: "a    b" => "a b"
    :param string: string a ser normalizada
    :return string: string normalizada
    """
    return ' '.join(string.split())


def parse_name(line):
    import re
    # se eu tiver um universo (MUTA, MUTANT, MUTANT-X)
    universe = ''
    if '|' in line:
        name, universe = line.split('|')
    else:
        name = line

    if '/' in name:
        name = name.split('/', maxsplit=1)[0]

    if ',' in name:
        name = ' '.join(name.split(',', maxsplit=2)[::-1])

    name = universe + ' ' + name

    return normaliza_espaco(re.sub('[,\|\-/]', '', name)).strip()


def main():
    """
    Trata o arquivo de super-heróis normalizando seus nomes:
    STARSHINE II/BRANDY => STARSHINE II
    RESTON, CLIVE => CLIVE RESTON
    STORM, JOHNNY | MUTA  => MUTA JOHNNY STORM
    """
    filename = "hero-network.csv"
    filename_out = "hero-network-norm.csv"
    with open(filename_out, 'w', newline='') as csv_write:
        # usando o pipe(|) como delimitador pois pipe não aparece nos dados, assim posso desabilitar
        # unquoting na hora de fazer o parse do CSV ganhando performance
        writer = csv.DictWriter(csv_write, fieldnames=['source', 'target'], delimiter=',',
                                quoting=csv.QUOTE_ALL, quotechar='"')

        heroes = set()
        with open(filename, newline='') as csv_read:
            reader = csv.reader(csv_read, delimiter=',', quotechar='"')
            rows = []
            for r in reader:
                source, target = r
                source, target = parse_name(source), parse_name(target)
                rows.append({'source': source, 'target': target})
                heroes.add(source)
                heroes.add(target)
        csv_write.seek(0)
        csv_write.write("#{}\n".format(len(heroes)))
        writer.writeheader()
        csv_write.seek(0, 2)
        shuffle(rows)
        writer.writerows(rows)


if __name__ == '__main__':
    main()
