import os
import sys
import argparse
import cairosvg

from alive_progress import alive_bar

def generate_icons(input_file, output_dir, sizes):
  if isinstance(output_dir, list):
    output_dir = output_dir[0]

  # Extract the icon name from input filename
  input_name = os.path.basename(input_file)
  input_name = os.path.splitext(input_name)[0]

  print(f'Building directory {output_dir}...')
  os.makedirs(output_dir, exist_ok = True)

  # Generate output filenames

  print(f'Generating icons from {input_file}...')

  with alive_bar(len(sizes)) as bar:
    for size in sizes:
      # Build the output directory for {size}x{size}

      size_dir = os.path.join(output_dir, f'{size}')

      print(f'Building directory {size_dir}...')
      os.makedirs(size_dir, exist_ok = True)

      # Build the output filename for {size}x{size}
      output_file = os.path.join(size_dir, f'{input_name}.png')

      # Convert the SVG icon to PNG
      print(f'Converting {input_file} to {output_file}...')
      cairosvg.svg2png(
        url           = input_file,
        write_to      = output_file,
        output_width  = size,
        output_height = size
      )

      # Update bar
      bar()

  print('Generation completed!')
  print(f'You can found icons in {output_dir}.')

def main():
  parser = argparse.ArgumentParser(
    description = 'Generate common application PNG icons from SVG input file.'
  )

  parser.add_argument(
    'input_file',
    type     = str,
    metavar  = 'INPUT_FILE',
    help     = 'input filename (with extension) that contains the SVG icon;'
  )

  parser.add_argument(
    '-o', '--output-dir',
    type     = str,
    dest     = 'output_dir',
    nargs    = 1,
    default  = './',
    help     = 'output directory to save generated PNG icons;'
  )

  parser.add_argument(
    '-s', '--sizes',
    type     = int,
    dest     = 'sizes',
    nargs    = '+',
    default  = [ 16, 20, 22, 24, 28, 32, 36, 48, 64, 72, 96, 128, 192, 256, 512, 1024 ],
    help     = 'list of sizes to convert the SVG icon to (e.g. -s 16 32 64).'
  )

  try:
    args = parser.parse_args()
  except:
    sys.exit(1)

  print(args)
  generate_icons(args.input_file, args.output_dir, args.sizes)

main()
