import sys
import onnx

if __name__ == "__main__":
    if(len(sys.argv) != 3):
        print("USAGE: python onnx_metadata_modify.py input.onnx output.onnx\n", file=sys.stderr)
        exit(1)

    input_onnx = sys.argv[1]
    output_onnx = sys.argv[2]
    model = onnx.load_model(input_onnx)

    model.producer_name = "nexaai"
    model.producer_version = "v1.0"

    for _ in range(len(model.metadata_props)):
        model.metadata_props.pop()

    meta_info = model.metadata_props.add()
    meta_info.key = 'onnx.infer'
    meta_info.value = 'onnxruntime'
    
    # meta_info = model.metadata_props.add()
    # meta_info.key = 'model_type'
    # meta_info.value = 'zipformer2'

    meta_info = model.metadata_props.add()
    meta_info.key = 'version'
    meta_info.value = '1'

    meta_info = model.metadata_props.add()
    meta_info.key = 'model_author'
    meta_info.value = 'nexaai'

    # meta_info = model.metadata_props.add()
    # meta_info.key = 'context_size'
    # meta_info.value = '2'

    # meta_info = model.metadata_props.add()
    # meta_info.key = 'vocab_size'
    # meta_info.value = '5224'

    # meta_info = model.metadata_props.add()
    # meta_info.key = 'joiner_dim'
    # meta_info.value = '512'

    onnx.save(model, output_onnx)