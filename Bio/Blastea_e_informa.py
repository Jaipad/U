from Bio.Blast import NCBIWWW
from Bio.Blast import NCBIXML
from Bio import Entrez
from Bio import SeqIO
import sys

def get_gene_info(gene_id):
    Entrez.email = "manugm_00@hotmail.com"
    with Entrez.efetch(db="nucleotide", id=gene_id, rettype="gb", retmode="text") as handle:
        record = SeqIO.read(handle, "genbank")

    especie = record.annotations.get("organism", "")
    gen = record.name

    source_features = [feature for feature in record.features if feature.type == "source"]
    if source_features:
        ubicacion = source_features[0].location
        qualifiers = source_features[0].qualifiers
        cromosoma = qualifiers.get("chromosome", [""])[0]
        hebra = ubicacion.strand
    else:
        ubicacion = ""
        cromosoma = ""
        hebra = ""

    numero_exones = sum(1 for feature in record.features if feature.type == "exon")

    return especie, gen, cromosoma, ubicacion, hebra, numero_exones


def main():
    secuencia = sys.argv[1]
    print("BLASTeando secuencia...")
    result_handle = NCBIWWW.qblast("blastn", "nt", secuencia)

    with open("resultado_blast.xml", "w") as out_handle:
        out_handle.write(result_handle.read())

    result_handle.close()
    print('archivo almacenado')


    result_handle = open("resultado_blast.xml", "r")
    blast_record = NCBIXML.read(result_handle)
    result_handle.close()


    first_hit = blast_record.alignments[0]
    gene_id = first_hit.accession

    print("Obteniendo información del gen...")
    species, gene_name, chromosome, ubicacion, strand, exons = get_gene_info(gene_id)

    print("Especie:", species)
    print("Gen al cual pertenece:", gene_name)
    print("Cromosoma en el que se encuentra:", chromosome)
    print("Ubicación y hebra (+/-):", ubicacion, strand)
    print("Número de exones que posee el gen:", exons)

main()